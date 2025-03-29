#include "Core/CoreMinimal.h"
#include "SwarmEngine.h"

KSwarmEngine::KSwarmEngine():
    bExitRequired(false)
{
}

KSwarmEngine::~KSwarmEngine()
{
}

void KSwarmEngine::Initialize()
{
}

void KSwarmEngine::Shutdown()
{
}

void KSwarmEngine::EngineTick(float DeltaTime)
{
    UNUSED_VAR(DeltaTime);
}

void KSwarmEngine::RequireEngineExit()
{
    bExitRequired = true;
}

bool KSwarmEngine::IsEngineExitRequired() const
{
    return bExitRequired;
}
