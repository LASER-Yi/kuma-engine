#pragma once

#include "SceneProxy.h"
#include "Shader.h"

#include <cstddef>
#include <memory>
#include <unordered_map>

struct FStaticMesh;
struct FSceneProxy;
struct FStateObject;
struct FRenderResource;
struct FSceneRenderResource;
struct FMeshRenderResource;
struct FMeshResourceDescriptor;

class KRenderer
{
public:
    virtual ~KRenderer() = default;

    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown();

    virtual void Enqueue(std::shared_ptr<FPrimitiveSceneProxy> InProxy);

    virtual void SetCamera(std::shared_ptr<FCameraSceneProxy> InCameraData);

public:
    virtual void Resize(size_t Width, size_t Height) = 0;

public:
    virtual const FShaderManager* GetShaderManager() const = 0;

    virtual std::shared_ptr<FSceneRenderResource> CreateSceneResource() = 0;

    virtual std::shared_ptr<FStateObject> CreateStateObject(
        const FShaderResourceRef Shader
    ) = 0;

    virtual std::shared_ptr<FMeshRenderResource> CreateMesh(
        const FMeshResourceDescriptor& InDescriptor
    ) = 0;

protected:
    std::weak_ptr<FCameraSceneProxy> CameraData;

    std::unordered_map<std::size_t, std::weak_ptr<FPrimitiveSceneProxy>>
        Proxies;
};
