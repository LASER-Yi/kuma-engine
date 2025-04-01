#pragma once

#include "Renderer.h"

#include <memory>

namespace Renderer
{

class KMetalDevice;
class KMetalViewport;

class KMetalRenderer : public IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
};

} // namespace Renderer
