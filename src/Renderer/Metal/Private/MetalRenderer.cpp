#include "MetalRenderer.h"

#include "Matrix.h"
#include "MetalCmdQueue.h"
#include "MetalDevice.h"
#include "MetalShader.h"
#include "MetalStateObject.h"
#include "MetalTransBuffer.h"
#include "MetalVertexBuffer.h"
#include "MetalViewport.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Vector.h"
#include "VertexBuffer.h"

#include <Foundation/NSAutoreleasePool.hpp>
#include <Foundation/NSTypes.hpp>
#include <Metal/MTLCommandBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <Metal/MTLRenderCommandEncoder.hpp>
#include <Metal/MTLRenderPass.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>
#include <simd/matrix_types.h>
#include <simd/simd.h>

#include <cassert>
#include <memory>

void KMetalRenderer::Initialize(void* WindowPtr)
{
    assert(WindowPtr != nullptr);

    Device = std::make_shared<KMetalDevice>();
    Viewport = std::make_shared<KMetalViewport>(WindowPtr, Device);
    CommandQueue = std::make_shared<KMetalCmdQueue>(Device);
    Shader = std::make_shared<FMetalShaderManager>(Device);
}

void KMetalRenderer::Update()
{
    if (Viewport->IsViewportReady() == false)
    {
        return;
    }

    NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();

    CA::MetalDrawable* Drawable = Viewport->GetDrawable();
    MTL::CommandBuffer* Cmd = CommandQueue->GetCmdBuffer();

    MTL::RenderPassDescriptor* ClearColorDesc =
        MTL::RenderPassDescriptor::alloc()->init();
    {
        MTL::RenderPassColorAttachmentDescriptor* ColorClearAttachment =
            ClearColorDesc->colorAttachments()->object(0);

        ColorClearAttachment->setTexture(Drawable->texture());
        ColorClearAttachment->setLoadAction(MTL::LoadActionClear);
        ColorClearAttachment->setClearColor(MTL::ClearColor(0.0, 0.0, 0.0, 1.0)
        );
        ColorClearAttachment->setStoreAction(MTL::StoreActionStore);

        MTL::RenderCommandEncoder* ClearColorEncoder =
            Cmd->renderCommandEncoder(ClearColorDesc);
        ClearColorEncoder->endEncoding();
    }

    MTL::RenderPassDescriptor* RenderDesc =
        MTL::RenderPassDescriptor::alloc()->init();
    {
        MTL::RenderPassColorAttachmentDescriptor* ColorAttachment =
            RenderDesc->colorAttachments()->object(0);
        ColorAttachment->setTexture(Drawable->texture());
        ColorAttachment->setLoadAction(MTL::LoadActionLoad);
        ColorAttachment->setStoreAction(MTL::StoreActionStore);

        for (const auto Proxy : Proxies)
        {
            if (Proxy.expired())
            {
                continue;
            }

            const auto SharedProxy = Proxy.lock();

            MTL::RenderCommandEncoder* Encoder =
                Cmd->renderCommandEncoder(RenderDesc);
            Encoder->setCullMode(MTL::CullModeBack);
            Encoder->setFrontFacingWinding(MTL::WindingCounterClockwise);

            const auto StateObject =
                std::static_pointer_cast<FMetalStateObject>(
                    SharedProxy->PipelineStateObject
                );
            Encoder->setRenderPipelineState(StateObject->Data);

            const auto VertexBuffer =
                std::static_pointer_cast<FMetalVertexBuffer>(
                    SharedProxy->VertexBuffer
                );
            Encoder->setVertexBuffer(VertexBuffer->Data, 0, 0);

            const auto ColorBuffer =
                std::static_pointer_cast<FMetalVertexBuffer>(
                    SharedProxy->ColorBuffer
                );
            Encoder->setVertexBuffer(ColorBuffer->Data, 0, 1);

            if (SharedProxy->Transform == nullptr)
            {
                const float AspectRatio =
                    static_cast<float>(Drawable->texture()->width()) /
                    static_cast<float>(Drawable->texture()->height());

                SharedProxy->Transform = std::make_shared<FMetalTransBuffer>(
                    Device, AspectRatio, SharedProxy->ComponentToWorld
                );
            }

            const auto TransformBuffer =
                std::static_pointer_cast<FMetalTransBuffer>(
                    SharedProxy->Transform
                );
            Encoder->setVertexBuffer(TransformBuffer->Data, 0, 2);

            Encoder->drawPrimitives(
                MTL::PrimitiveTypeTriangle, NS::UInteger(0),
                NS::UInteger(SharedProxy->VertexCount)
            );

            Encoder->endEncoding();
        }
    }

    Cmd->presentDrawable(Drawable);
    Cmd->commit();

    RenderDesc->release();
    ClearColorDesc->release();

    Pool->release();
}

void KMetalRenderer::Shutdown()
{
    KRenderer::Shutdown();

    Viewport = nullptr;
    Device = nullptr;
}

const FShaderManager* KMetalRenderer::GetShaderManager() const
{
    assert(Shader);
    return Shader.get();
}

FStateObjectRef KMetalRenderer::CreateStateObject(
    const FShaderResourceRef Shader
)
{
    std::shared_ptr<FMetalShaderResource> MetalShader =
        std::static_pointer_cast<FMetalShaderResource>(Shader);

    return std::make_shared<FMetalStateObject>(Device->Get(), MetalShader);
}

FVertexBufferRef KMetalRenderer::CreateVertexBuffer(
    const std::vector<Math::FVector>& InVertex
)
{
    return std::make_shared<FMetalVertexBuffer>(Device->Get(), InVertex);
}
