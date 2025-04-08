#include "MetalViewport.h"

#include <AppKit/NSWindow.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Metal/MTLPixelFormat.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

#include "MetalDevice.h"

KMetalViewport::KMetalViewport(
    std::shared_ptr<KMetalDevice> InDevice, void* InWindow
)
    : Window(InWindow), bPendingResizeRequest(false)
{
    assert(InDevice != nil);
    assert(InWindow != nil);

    NSWindow* CocoaWindow = (NSWindow*)Window;

    CA::MetalLayer* Layer = CA::MetalLayer::layer();

    const NSRect contentRect = [CocoaWindow contentLayoutRect];
    Layer->setDevice(InDevice->Get());
    Layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    Layer->setDrawableSize(contentRect.size);

    [[CocoaWindow contentView] setLayer:(CALayer*)Layer];
    [[CocoaWindow contentView] setWantsLayer:YES];

    MetalLayer = Layer;
}

KMetalViewport::~KMetalViewport()
{
    Window = nil;

    MetalLayer->release();
    MetalLayer = nil;
}

void KMetalViewport::RequestResize(size_t Width, size_t Height)
{
    bPendingResizeRequest = true;
}

void KMetalViewport::ResizeViewport()
{
    if (MetalLayer)
    {
        NSWindow* CocoaWindow = (NSWindow*)Window;
        const NSRect contentRect = [CocoaWindow contentLayoutRect];
        MetalLayer->setDrawableSize(contentRect.size);
    }
}

bool KMetalViewport::IsViewportReady() const { return MetalLayer != nil; }

CA::MetalDrawable* KMetalViewport::GetDrawable()
{
    if (bPendingResizeRequest)
    {
        bPendingResizeRequest = false;
        ResizeViewport();
    }
    return MetalLayer->nextDrawable();
}
