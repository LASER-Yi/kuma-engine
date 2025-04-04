#pragma once

#include "CoreMinimal.h"
#include <memory>

class KRenderer;

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

    std::shared_ptr<KRenderer> GetRenderer() const;

private:
    bool bExitRequired = false;

    std::shared_ptr<KRenderer> Renderer;
};
