#pragma once

#include "SceneProxy.h"

class IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown() = 0;

    virtual void Enqueue(const FSceneProxy& InProxy) = 0;
};
