#pragma once

#include <memory>

namespace CA
{
class MetalLayer;
class MetalDrawable;
} // namespace CA
class KMetalDevice;

class KMetalViewport
{
public:
    KMetalViewport(void* InWindow, std::shared_ptr<KMetalDevice> InDevice);

    ~KMetalViewport();

    CA::MetalDrawable* GetDrawable();

private:
    void* Window;
    CA::MetalLayer* MetalLayer;
};
