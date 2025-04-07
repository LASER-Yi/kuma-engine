#pragma once

#include "MetalShader.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Shader.h"

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

public:
    virtual const FShaderManager* GetShaderManager() const override;

    virtual FStateObjectRef CreateStateObject(const FShaderResourceRef Shader
    ) override;

    virtual FVertexBufferRef CreateVertexBuffer(
        const std::vector<Math::FVector>& InVertex
    ) override;

private:
    KMetalDeviceRef Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;

    std::shared_ptr<FMetalShaderManager> Shader;
};
