#pragma once

namespace MTL
{
class Device;
}

class KMetalDevice
{
public:
    KMetalDevice();

    ~KMetalDevice();

    MTL::Device* Get() const { return MetalDevice; }

private:
    MTL::Device* MetalDevice;
};
