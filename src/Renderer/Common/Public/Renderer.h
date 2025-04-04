#pragma once

#include "StateObject.h"
#include "Vector.h"
#include "VertexBuffer.h"

#include <memory>
#include <vector>

struct FSceneProxy;

class KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown();

    virtual void Enqueue(std::shared_ptr<FSceneProxy> InProxy);

public:
    virtual FStateObjectRef CreateStateObject(
        const char* Shader, const char* Vertex, const char* Fragment
    ) = 0;

    virtual FVertexBufferRef
    CreateVertexBuffer(const std::vector<FVector>& InVertex) = 0;

protected:
    std::vector<std::weak_ptr<FSceneProxy>> Proxies;
};
