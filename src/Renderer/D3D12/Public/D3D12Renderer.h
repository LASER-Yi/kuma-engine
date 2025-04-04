#pragma once

#include "Renderer.h"
#include "SceneProxy.h"

class KD3D12Renderer : public KRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;
    virtual void Shutdown() override;

    virtual void Enqueue(const FSceneProxy& InProxy) override;
};
