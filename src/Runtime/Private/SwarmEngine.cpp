#include "CoreMinimal.h"

#include "SwarmEngine.h"
#include <cassert>

KSwarmEngine::KSwarmEngine() : bExitRequired(false) {}

KSwarmEngine::~KSwarmEngine() {}

void KSwarmEngine::Initialize()
{
    SwarmManager = std::make_shared<Swarm::Manager>();
    assert(SwarmManager != nullptr && "Failed to create SwarmManager");
}

void KSwarmEngine::Shutdown() {}

void KSwarmEngine::EngineTick(float DeltaTime)
{
    SwarmManager->Update(DeltaTime);
}

void KSwarmEngine::RequireEngineExit() { bExitRequired = true; }

bool KSwarmEngine::IsEngineExitRequired() const { return bExitRequired; }
