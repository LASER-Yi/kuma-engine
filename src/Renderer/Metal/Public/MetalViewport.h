#pragma once

#include "Metal/MTLDevice.hpp"

namespace Renderer
{

class KMetalViewport
{
public:
    KMetalViewport(void* InWindow);

    void Initialize(MTL::Device* InDevice);

private:
    void* Window;
};

} // namespace Renderer
