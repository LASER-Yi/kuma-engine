
#include "MetalDevice.h"
#include "Metal/MTLDevice.hpp"

namespace Renderer
{

void KMetalDevice::Initialize()
{
    MetalDevice = MTL::CreateSystemDefaultDevice();
}

void KMetalDevice::Shutdown()
{
    if (MetalDevice)
    {
        MetalDevice->release();
        MetalDevice = nullptr;
    }
}

} // namespace Renderer
