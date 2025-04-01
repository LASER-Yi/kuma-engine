#include "MetalViewport.h"

#include "Metal/MTLPixelFormat.hpp"
#include "QuartzCore/CAMetalDrawable.hpp"
#include "QuartzCore/CAMetalLayer.hpp"
#include <AppKit/NSWindow.h>

#include "MetalDevice.h"

KMetalViewport::KMetalViewport(
    void* InWindow, std::shared_ptr<KMetalDevice> InDevice
)
    : Window(InWindow)
{
    assert(InDevice != nil);
    assert(InWindow != nil);

    NSWindow* CocoaWindow = (NSWindow*)Window;

    MetalLayer = CA::MetalLayer::layer();
    MetalLayer->setDevice(InDevice->Get());
    MetalLayer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    [[CocoaWindow contentView] setLayer:(CALayer*)MetalLayer];
    [[CocoaWindow contentView] setWantsLayer:YES];
}

KMetalViewport::~KMetalViewport() {}

CA::MetalDrawable* KMetalViewport::GetDrawable()
{
    return MetalLayer->nextDrawable();
}
