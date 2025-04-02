#pragma once

#include "CoreMinimal.h"
#include <memory>

class IRenderer;

class KEngine
{
public:
    KEngine();
    virtual ~KEngine();

    virtual void Initialize();
    virtual void Shutdown();

    virtual void EngineTick(float DeltaTime);

    void RequireEngineExit();

    bool IsEngineExitRequired() const;

    std::shared_ptr<IRenderer> GetRenderer() const;

private:
    bool bExitRequired = false;

    std::shared_ptr<IRenderer> Renderer;
};
