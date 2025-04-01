
#include "MetalDevice.h"
#include "Metal/MTLDevice.hpp"

KMetalDevice::KMetalDevice() { MetalDevice = MTL::CreateSystemDefaultDevice(); }

KMetalDevice::~KMetalDevice()
{
    if (MetalDevice)
    {
        MetalDevice->release();
        MetalDevice = nullptr;
    }
}
