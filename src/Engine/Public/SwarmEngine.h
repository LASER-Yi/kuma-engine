#pragma once
#include "Core/CoreMinimal.h"

#include <memory>

#include "Swarm/SwarmManager.h"

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

protected:
    std::shared_ptr<Swarm::Manager> SwarmManager;

private:
    bool bExitRequired = false;
};
