#pragma once

#include "Renderer.h"
#include "Shader.h"

#include <memory>

class KMetalDevice;
class KMetalViewport;
class KMetalCmdQueue;
struct FMetalShaderManager;

class KMetalRenderer : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

public:
    virtual const FShaderManager* GetShaderManager() const override;

    virtual std::shared_ptr<FStateObject> CreateStateObject(
        const FShaderResourceRef Shader
    ) override;

    virtual std::shared_ptr<FRenderResource> CreateVertexBuffer(
        const std::vector<Math::FVector>& InVertex
    ) override;

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;

    std::shared_ptr<FMetalShaderManager> Shader;
};
