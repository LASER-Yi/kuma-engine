#pragma once

#include <memory>
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

using KMetalDeviceRef = std::shared_ptr<KMetalDevice>;
