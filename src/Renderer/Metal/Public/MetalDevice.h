#pragma once

#include "Metal/MTLDevice.hpp"
namespace Renderer
{

class KMetalDevice
{
public:
    void Initialize();

    void Shutdown();

private:
    MTL::Device* MetalDevice;
};

} // namespace Renderer
