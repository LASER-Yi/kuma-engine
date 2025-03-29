#pragma once

#include "CoreMinimal.h"

class KEngine
{
public:
    KEngine();
    ~KEngine();

    void Initialize();
    void Shutdown();

    void EngineTick(float DeltaTime);

    void RequireEngineExit();

    bool IsEngineExitRequired() const;

private:
    bool bExitRequired = false;
};
