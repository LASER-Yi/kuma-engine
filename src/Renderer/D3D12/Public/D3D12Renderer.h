#pragma once

#include "Renderer.h"

struct FD3D12Viewport;
struct FD3D12CmdQueue;
struct FD3D12ShaderManager;
struct FD3D12Device;

class KD3D12Renderer : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;
    virtual void Shutdown() override;

    virtual void Resize(size_t Width, size_t Height) override;

    virtual const FShaderManager* GetShaderManager() const override;

    virtual std::shared_ptr<FSceneRenderResource> CreateSceneResource(
    ) override;

    virtual std::shared_ptr<FStateObject> CreateStateObject(
        const FShaderResourceRef Shader
    ) override;

    virtual std::shared_ptr<FMeshRenderResource> CreateMesh(
        const FMeshResourceDescriptor& InDescriptor
    ) override;

private:
    std::shared_ptr<FD3D12ShaderManager> ShaderManager;

    std::shared_ptr<FD3D12Device> Device;
    std::shared_ptr<FD3D12CmdQueue> CommandQueue;
    std::shared_ptr<FD3D12Viewport> Viewport;
};
