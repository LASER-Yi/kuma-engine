#pragma once

#include "Matrix.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "SceneResource.h"
#include "Shader.h"

#include <memory>

namespace MTL
{
class RenderCommandEncoder;
class Texture;
} // namespace MTL

class KMetalDevice;
class KMetalViewport;
class KMetalCmdQueue;
struct FMetalShaderManager;

class KMetalRenderer final : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

    virtual void Resize(size_t Width, size_t Height) override;

public:
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
    /**
     * Get the matrix to transform from Kuma coordination system to metal
     * coordination system
     */
    const Math::FMatrix& GetCoordinationMatrix() const;

    void UpdateSceneBuffers(MTL::Texture* Backbuffer);

    void EncodePrimitive(
        MTL::RenderCommandEncoder* Encoder, const FSceneProxy* Proxy
    ) const;

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;

    std::shared_ptr<FMetalShaderManager> Shader;
};
