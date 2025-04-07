#pragma once

#include "Renderer.h"
#include "SceneProxy.h"

struct FD3D12ShaderManager;

class KD3D12Renderer : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;
    virtual void Shutdown() override;

    virtual const FShaderManager* GetShaderManager() const override;

    virtual FStateObjectRef CreateStateObject(const FShaderResourceRef Shader) override;
    virtual FVertexBufferRef CreateVertexBuffer(const std::vector<Math::FVector>& InVertex) override;

private:

    std::shared_ptr<FD3D12ShaderManager> ShaderManager;
};
