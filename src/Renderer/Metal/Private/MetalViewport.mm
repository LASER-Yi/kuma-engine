#include "MetalViewport.h"

#include "Metal/MTLPixelFormat.hpp"
#include "QuartzCore/CAMetalDrawable.hpp"
#include "QuartzCore/CAMetalLayer.hpp"
#include <AppKit/NSWindow.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

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
    MetalLayer->setDrawableSize(CGSizeMake(800, 600)
    ); // TODO: match the size of NSWindow

    [[CocoaWindow contentView] setLayer:(CALayer*)MetalLayer];
    [[CocoaWindow contentView] setWantsLayer:YES];
}

KMetalViewport::~KMetalViewport() {}

CA::MetalDrawable* KMetalViewport::GetDrawable()
{
    return MetalLayer->nextDrawable();
}
