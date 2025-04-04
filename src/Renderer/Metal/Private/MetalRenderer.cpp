#include "MetalRenderer.h"
#include "Foundation/NSString.hpp"
#include "Foundation/NSTypes.hpp"
#include "Metal/MTLLibrary.hpp"
#include "Metal/MTLPixelFormat.hpp"
#include "Metal/MTLRenderPipeline.hpp"
#include "Metal/MTLResource.hpp"
#include "MetalRenderData.h"
#include "MetalStateObject.h"
#include "MetalVertexBuffer.h"
#include "Renderer.h"
#include "Vector.h"
#include "VertexBuffer.h"

#include <Foundation/NSAutoreleasePool.hpp>
#include <Metal/MTLCommandBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <Metal/MTLRenderCommandEncoder.hpp>
#include <Metal/MTLRenderPass.hpp>
#include <MetalCmdQueue.h>
#include <MetalDevice.h>
#include <MetalViewport.h>
#include <QuartzCore/CAMetalDrawable.hpp>

#include <cassert>
#include <memory>

void KMetalRenderer::Initialize(void* WindowPtr)
{
    assert(WindowPtr != nullptr);

    Device = std::make_shared<KMetalDevice>();
    Viewport = std::make_shared<KMetalViewport>(WindowPtr, Device);
    CommandQueue = std::make_shared<KMetalCmdQueue>(Device);
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

            const auto StateObject =
                std::static_pointer_cast<FMetalStateObject>(
                    SharedProxy->PipelineStateObject
                );
            Encoder->setRenderPipelineState(StateObject->Data);

            for (int i = 0; i < SharedProxy->VertexBufferCount; ++i)
            {
                const auto VertexBuffer =
                    std::static_pointer_cast<FMetalVertexBuffer>(
                        SharedProxy->VertexBuffers[i]
                    );

                // We use separate buffer to store the vertex for now
                Encoder->setVertexBuffer(VertexBuffer->Data, 0, i);
            }

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

FStateObjectRef KMetalRenderer::CreateStateObject(
    const char* Shader, const char* Vertex, const char* Fragment
)
{
    return std::make_shared<FMetalStateObject>(
        Device->Get(), Shader, Vertex, Fragment
    );
}

FVertexBufferRef
KMetalRenderer::CreateVertexBuffer(const std::vector<FVector>& InVertex)
{
    return std::make_shared<FMetalVertexBuffer>(Device->Get(), InVertex);
}
