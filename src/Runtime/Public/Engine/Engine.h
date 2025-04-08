#pragma once

#include "CoreMinimal.h"
#include <memory>

class KRenderer;

struct FEngineInitializationContext
{
    const char* CmdLine;
    void* WindowHandle;
};

class KEngine
{
public:
    KEngine();
    virtual ~KEngine();

    virtual void Initialize(const FEngineInitializationContext& Context);
    virtual void Update();
    virtual void Shutdown();

    void RequestResize(size_t Width, size_t Height);
    void RequireEngineExit();

    bool IsEngineExitRequired() const;
    bool IsEngineShutdown() const;

    std::shared_ptr<KRenderer> GetRenderer() const;

    double GetWorldTimeSeconds() const;

private:
    bool bExitRequired = false;
    bool bShutdown = false;

    std::shared_ptr<KRenderer> Renderer;

    double LastTickWorldTimeSeconds = 0.0f;
};
