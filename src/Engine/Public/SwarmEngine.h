#pragma once

#include <vector>


class KSwarmEngine
{
public:
    KSwarmEngine();
    ~KSwarmEngine();

    void Initialize();
    void Shutdown();

    void EngineTick(float DeltaTime);

    void RequireEngineExit();

    bool IsEngineExitRequired() const;

private:
    bool bExitRequired = false;
};
