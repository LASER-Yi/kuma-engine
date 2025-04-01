#pragma once

#include "Metal/MTLDevice.hpp"

class KMetalDevice
{
public:
    KMetalDevice();

    ~KMetalDevice();

    MTL::Device* Get() const { return MetalDevice; }

private:
    MTL::Device* MetalDevice;
};
