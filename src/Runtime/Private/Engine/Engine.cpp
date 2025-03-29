#include "Engine/Engine.h"
#include "Swarm/SwarmManager.h"

KEngine::KEngine() : bExitRequired(false) {}

KEngine::~KEngine() {}

void KEngine::Initialize() {}

void KEngine::Shutdown() {}

void KEngine::EngineTick(float DeltaTime)
{
    Swarm::Manager::Get()->Update(DeltaTime);
}

void KEngine::RequireEngineExit() { bExitRequired = true; }

bool KEngine::IsEngineExitRequired() const { return bExitRequired; }
