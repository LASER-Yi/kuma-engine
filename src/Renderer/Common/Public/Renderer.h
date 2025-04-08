#pragma once

#include "Shader.h"
#include "Vector.h"

#include <memory>
#include <vector>

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

    virtual void Enqueue(std::shared_ptr<FSceneProxy> InProxy);

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
    std::vector<std::weak_ptr<FSceneProxy>> Proxies;
};
