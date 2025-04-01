#include "MetalViewport.h"

#include "Metal/MTLDevice.hpp"
#include "Metal/MTLPixelFormat.hpp"
#include "QuartzCore/CAMetalLayer.hpp"
#include <AppKit/NSWindow.h>

namespace Renderer
{

KMetalViewport::KMetalViewport(void* InWindow) : Window(InWindow) {}

void KMetalViewport::Initialize(MTL::Device* InDevice)
{
    assert(InDevice != nil);
    assert(Window != nil);

    NSWindow* CocoaWindow = (NSWindow*)Window;

    auto* Layer = CA::MetalLayer::layer();
    Layer->setDevice(InDevice);
    Layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    [[CocoaWindow contentView] setLayer:(CALayer*)Layer];
    [[CocoaWindow contentView] setWantsLayer:YES];
}
} // namespace Renderer
