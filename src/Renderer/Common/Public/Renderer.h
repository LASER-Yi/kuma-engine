#pragma once

#include "Shader.h"
#include "Vector.h"

#include <memory>
#include <vector>

struct FSceneProxy;
struct FStateObject;
struct FRenderResource;

class KRenderer
{
public:
    virtual ~KRenderer() = default;

    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown();

    virtual void Enqueue(std::shared_ptr<FSceneProxy> InProxy);

public:
    virtual const FShaderManager* GetShaderManager() const = 0;

    virtual std::shared_ptr<FStateObject> CreateStateObject(
        const FShaderResourceRef Shader
    ) = 0;

    virtual std::shared_ptr<FRenderResource> CreateVertexBuffer(
        const std::vector<Math::FVector>& InVertex
    ) = 0;

protected:
    std::vector<std::weak_ptr<FSceneProxy>> Proxies;
};
