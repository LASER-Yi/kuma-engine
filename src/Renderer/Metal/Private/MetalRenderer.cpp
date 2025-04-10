#include "MetalRenderer.h"

#include "Matrix.h"
#include "MeshResource.h"
#include "Metal/MTLStageInputOutputDescriptor.hpp"
#include "Metal/MTLTexture.hpp"
#include "MetalCmdQueue.h"
#include "MetalDevice.h"
#include "MetalMesh.h"
#include "MetalScene.h"
#include "MetalShader.h"
#include "MetalStateObject.h"
#include "MetalViewport.h"
#include "Renderer.h"
#include "Rotator.h"
#include "SceneProxy.h"
#include "SceneResource.h"
#include "StateObject.h"

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
    Viewport = std::make_shared<KMetalViewport>(Device, WindowPtr);
    CommandQueue = std::make_shared<KMetalCmdQueue>(Device);
    Shader = std::make_shared<FMetalShaderManager>(Device);
}

void KMetalRenderer::Update()
{
    if (Viewport->IsViewportReady() == false)
    {
        return;
    }

    std::shared_ptr<FCameraSceneProxy> Camera = CameraData.lock();
    if (Camera == nullptr)
    {
        return;
    }

    NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();

    CA::MetalDrawable* Drawable = Viewport->GetDrawable();

    // Update camera data
    {
        const Math::FMatrix& Coordination = GetCoordinationMatrix();

        const MTL::Texture* SceneColor = Drawable->texture();

        const FRendererCameraDescriptor CameraDesc = {
            .FieldOfView = Camera->FieldOfView,
            .AspectRatio = static_cast<float>(SceneColor->width()) /
                           static_cast<float>(SceneColor->height()),
            .WorldToCamera = Camera->ComponentToWorld * Coordination,
            .Near = Camera->NearClip,
            .Far = Camera->FarClip
        };

        UpdateSceneBuffers(CameraDesc);
    }

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

        for (const auto& [Component, Proxy] : Proxies)
        {
            if (Proxy.expired())
            {
                continue;
            }

            const auto SceneProxy = Proxy.lock();

            MTL::RenderCommandEncoder* Encoder =
                Cmd->renderCommandEncoder(RenderDesc);

            EncodePrimitive(Encoder, SceneProxy.get());

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

void KMetalRenderer::Resize(size_t Width, size_t Height)
{
    if (Viewport)
    {
        Viewport->RequestResize(Width, Height);
    }
}

const FShaderManager* KMetalRenderer::GetShaderManager() const
{
    assert(Shader);
    return Shader.get();
}

std::shared_ptr<FSceneRenderResource> KMetalRenderer::CreateSceneResource()
{
    return std::make_shared<FMetalSceneResource>(Device);
}

std::shared_ptr<FStateObject> KMetalRenderer::CreateStateObject(
    const FShaderResourceRef Shader
)
{
    std::shared_ptr<FMetalShaderResource> MetalShader =
        std::static_pointer_cast<FMetalShaderResource>(Shader);

    return std::make_shared<FMetalStateObject>(Device->Get(), MetalShader);
}

std::shared_ptr<FMeshRenderResource> KMetalRenderer::CreateMesh(
    const FMeshResourceDescriptor& InDescriptor
)
{
    return std::make_shared<FMetalMeshResource>(Device, InDescriptor);
}

const Math::FMatrix& KMetalRenderer::GetCoordinationMatrix() const
{
    static const Math::FMatrix Matrix =
        Math::FMatrix::MakeRotation(Math::EAxis::Y, Math::FDegrees(90));

    return Matrix;
}

void KMetalRenderer::UpdateSceneBuffers(
    const FRendererCameraDescriptor& CameraDesc
)
{
    for (const auto& [Component, Proxy] : Proxies)
    {
        if (Proxy.expired())
        {
            continue;
        }

        auto SceneProxy = Proxy.lock();

        const FRendererPrimitiveDescriptor PrimitiveDesc = {
            .ModelToWorld = SceneProxy->ComponentToWorld
        };

        SceneProxy->SceneBuffer->Update(CameraDesc, PrimitiveDesc);
    }
}

void KMetalRenderer::EncodePrimitive(
    MTL::RenderCommandEncoder* Encoder, const FPrimitiveSceneProxy* Proxy
) const
{
    assert(Encoder);
    assert(Proxy);

    Encoder->setCullMode(MTL::CullModeBack);
    Encoder->setFrontFacingWinding(MTL::WindingCounterClockwise);

    const auto StateObject =
        std::static_pointer_cast<FMetalStateObject>(Proxy->PipelineStateObject);
    Encoder->setRenderPipelineState(StateObject->Data);

    const auto MeshResource =
        std::static_pointer_cast<FMetalMeshResource>(Proxy->MeshResource);
    Encoder->setVertexBuffer(MeshResource->VertexBuffer, 0, 0);

    const auto SceneBuffer =
        std::static_pointer_cast<FMetalSceneResource>(Proxy->SceneBuffer);
    Encoder->setVertexBuffer(SceneBuffer->Data, 0, 1);

    Encoder->drawIndexedPrimitives(
        MTL::PrimitiveTypeTriangle, NS::UInteger(MeshResource->VertexCount),
        MTL::IndexTypeUInt16, MeshResource->IndexBuffer, 0, 1
    );
}
