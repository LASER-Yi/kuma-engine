#pragma once

#include "CoreMinimal.h"
#include <memory>

class KRenderer;

class KEngine
{
public:
    KEngine();
    virtual ~KEngine();

    virtual void SetWindow(void* Handle);

    virtual void Initialize();
    virtual void Update();
    virtual void Shutdown();

    void RequireEngineExit();

    bool IsEngineExitRequired() const;

    std::shared_ptr<KRenderer> GetRenderer() const;

    double GetWorldTimeSeconds() const;

private:
    bool bExitRequired = false;

    void* WindowHandle;
    std::shared_ptr<KRenderer> Renderer;

    double LastTickWorldTimeSeconds = 0.0f;
};
