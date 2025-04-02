#include "MetalRenderer.h"
#include "Foundation/NSString.hpp"
#include "Metal/MTLLibrary.hpp"
#include "Metal/MTLPixelFormat.hpp"
#include "Metal/MTLRenderPipeline.hpp"
#include "PipelineState.h"

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
    MTL::CommandBuffer* Cmd = CommandQueue->AllocCmd();

    MTL::RenderPassDescriptor* RenderDescriptor =
        MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor* ColorAttachment =
        RenderDescriptor->colorAttachments()->object(0);
    ColorAttachment->setTexture(Drawable->texture());
    ColorAttachment->setLoadAction(MTL::LoadActionClear);
    ColorAttachment->setClearColor(MTL::ClearColor(1.0, 0.0, 0.0, 1.0));
    ColorAttachment->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder* Encoder =
        Cmd->renderCommandEncoder(RenderDescriptor);
    Encoder->endEncoding();

    Cmd->presentDrawable(Drawable);
    Cmd->commit();

    RenderDescriptor->release();

    Pool->release();
}

void KMetalRenderer::Shutdown()
{
    Viewport = nullptr;
    Device = nullptr;
}

FPipelineStateObject
KMetalRenderer::PreparePipelineState(const FPipelineDefinition& InDefinition)
{
    NS::Error* Error = nullptr;

    MTL::Device* MetalDevice = Device->Get();
    assert(MetalDevice);

    MTL::Library* Library = MetalDevice->newLibrary(
        NS::String::string(InDefinition.shader, NS::UTF8StringEncoding),
        nullptr, &Error
    );

    if (Library == nullptr)
    {
        return {.Data = nullptr};
    }

    MTL::Function* VertexFunc = Library->newFunction(NS::String::string(
        InDefinition.vertexEntrypoint, NS::UTF8StringEncoding
    ));
    MTL::Function* FragmentFunc = Library->newFunction(NS::String::string(
        InDefinition.fragmentEntrypoint, NS::UTF8StringEncoding
    ));

    MTL::RenderPipelineDescriptor* Desc =
        MTL::RenderPipelineDescriptor::alloc()->init();

    Desc->setVertexFunction(VertexFunc);
    Desc->setFragmentFunction(FragmentFunc);

    Desc->colorAttachments()->object(0)->setPixelFormat(
        MTL::PixelFormatBGRA8Unorm_sRGB
    );

    MTL::RenderPipelineState* StateObject =
        MetalDevice->newRenderPipelineState(Desc, &Error);

    assert(StateObject);

    VertexFunc->release();
    FragmentFunc->release();
    Desc->release();
    Library->release();

    return {.Data = StateObject};
}

void KMetalRenderer::ReleasePipelineState(FPipelineStateObject* StateObject)
{
    assert(StateObject);

    MTL::RenderPipelineState* MetalStateObject =
        reinterpret_cast<MTL::RenderPipelineState*>(StateObject->Data);

    MetalStateObject->release();
    StateObject->Data = nullptr;
}
