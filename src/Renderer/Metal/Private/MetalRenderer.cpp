#include "MetalRenderer.h"
#include "MetalDevice.h"
#include "MetalViewport.h"
#include <memory>

namespace Renderer
{

void KMetalRenderer::Initialize(void* WindowPtr)
{
    assert(WindowPtr != nullptr);

    Device = std::make_shared<KMetalDevice>();
    Viewport = std::make_shared<KMetalViewport>(WindowPtr);
}

void KMetalRenderer::Update() {}

void KMetalRenderer::Shutdown() { Device->Shutdown(); }

} // namespace Renderer
