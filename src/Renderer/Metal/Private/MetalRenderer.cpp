#include "MetalRenderer.h"
#include "Foundation/NSString.hpp"
#include "Foundation/NSTypes.hpp"
#include "Metal/MTLLibrary.hpp"
#include "Metal/MTLPixelFormat.hpp"
#include "Metal/MTLRenderPipeline.hpp"
#include "Metal/MTLResource.hpp"
#include "MetalRenderData.h"
#include "Vector.h"

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
#include <cstring>
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

    MTL::RenderPassDescriptor* RenderDescriptor =
        MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor* ColorAttachment =
        RenderDescriptor->colorAttachments()->object(0);
    ColorAttachment->setTexture(Drawable->texture());
    ColorAttachment->setLoadAction(MTL::LoadActionLoad);
    // ColorAttachment->setClearColor(MTL::ClearColor(0.0, 0.0, 0.0, 1.0));
    ColorAttachment->setStoreAction(MTL::StoreActionStore);

    for (const FMetalRenderData& RenderData :
         GetFrameRenderData<FMetalRenderData>())
    {
        MTL::RenderCommandEncoder* Encoder =
            Cmd->renderCommandEncoder(RenderDescriptor);

        Encoder->setRenderPipelineState(RenderData.State);
        Encoder->setVertexBuffer(RenderData.VertexPos, 0, 0);
        Encoder->setVertexBuffer(RenderData.VertexColor, 0, 1);

        Encoder->drawPrimitives(
            MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0),
            NS::UInteger(RenderData.VertexCount)
        );

        Encoder->endEncoding();
    }

    Cmd->presentDrawable(Drawable);
    Cmd->commit();

    for (const FMetalRenderData& RenderData :
         GetFrameRenderData<FMetalRenderData>())
    {
        RenderData.State->release();
        RenderData.VertexPos->release();
        RenderData.VertexColor->release();
    }
    FrameRenderData.resize(0);

    RenderDescriptor->release();

    Pool->release();
}

void KMetalRenderer::Shutdown()
{
    Viewport = nullptr;
    Device = nullptr;
}

void KMetalRenderer::Enqueue(const FSceneProxy& InProxy)
{
    FMetalRenderData* RenderData = AllocateFrameRenderData<FMetalRenderData>();

    MTL::Device* MetalDevice = Device->Get();
    assert(MetalDevice);

    NS::Error* Error = nullptr;

    // TODO: Cache and reuse PSO
    {
        NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();

        MTL::Library* Library = MetalDevice->newLibrary(
            NS::String::string(InProxy.Shader, NS::UTF8StringEncoding), nullptr,
            &Error
        );

        assert(Library);

        MTL::Function* VertexFunc = Library->newFunction(
            NS::String::string(InProxy.VertexEntrypoint, NS::UTF8StringEncoding)
        );
        MTL::Function* FragmentFunc = Library->newFunction(NS::String::string(
            InProxy.FragmentEntrypoint, NS::UTF8StringEncoding
        ));

        MTL::RenderPipelineDescriptor* Desc =
            MTL::RenderPipelineDescriptor::alloc()->init();
        Desc->setVertexFunction(VertexFunc);
        Desc->setFragmentFunction(FragmentFunc);
        Desc->colorAttachments()->object(0)->setPixelFormat(
            MTL::PixelFormatBGRA8Unorm
        );

        MTL::RenderPipelineState* StateObject =
            MetalDevice->newRenderPipelineState(Desc, &Error);

        assert(StateObject);

        RenderData->State = StateObject;

        VertexFunc->release();
        FragmentFunc->release();
        Desc->release();
        Library->release();

        Pool->release();
    }

    assert(InProxy.Vertices.size() == InProxy.Colors.size());
    RenderData->VertexCount = InProxy.Vertices.size();

    // TODO: Cache and reuse vertex data
    {
        const size_t VertexDataSize = InProxy.Vertices.size() * sizeof(FVector);

        MTL::Buffer* VertexBuffer = MetalDevice->newBuffer(
            VertexDataSize, MTL::ResourceStorageModeManaged
        );

        std::memcpy(
            VertexBuffer->contents(), InProxy.Vertices.data(), VertexDataSize
        );
        VertexBuffer->didModifyRange(NS::Range::Make(0, VertexBuffer->length())
        );

        RenderData->VertexPos = VertexBuffer;
    }

    // TODO: Cache and reuse color data
    {
        const size_t ColorDataSize = InProxy.Colors.size() * sizeof(FVector);

        MTL::Buffer* ColorBuffer = MetalDevice->newBuffer(
            ColorDataSize, MTL::ResourceStorageModeManaged
        );

        std::memcpy(
            ColorBuffer->contents(), InProxy.Colors.data(), ColorDataSize
        );
        ColorBuffer->didModifyRange(NS::Range::Make(0, ColorBuffer->length()));

        RenderData->VertexColor = ColorBuffer;
    }
}
