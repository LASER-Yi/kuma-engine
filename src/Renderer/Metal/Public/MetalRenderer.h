#pragma once

#include "Renderer.h"
#include "SceneProxy.h"

#include <memory>

class KMetalDevice;
class KMetalViewport;
class KMetalCmdQueue;

class KMetalRenderer : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

    virtual FStateObjectRef CreateStateObject(
        const char* Shader, const char* Vertex, const char* Fragment
    ) override;

    virtual FVertexBufferRef
    CreateVertexBuffer(const std::vector<FVector>& InVertex) override;

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;
};
