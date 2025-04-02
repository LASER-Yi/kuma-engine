#include "MetalRenderer.h"

#include <Foundation/NSAutoreleasePool.hpp>
#include <Metal/MTLCommandBuffer.hpp>
#include <Metal/MTLRenderCommandEncoder.hpp>
#include <Metal/MTLRenderPass.hpp>
#include <MetalCmdQueue.h>
#include <MetalDevice.h>
#include <MetalViewport.h>
#include <QuartzCore/CAMetalDrawable.hpp>

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
