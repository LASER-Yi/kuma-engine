#pragma once

#include "CoreMinimal.h"

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

private:
    bool bExitRequired = false;
};
