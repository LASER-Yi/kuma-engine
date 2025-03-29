#include "KumaEngine.h"

KKumaEngine::KKumaEngine():
    bExitRequired(false)
{
}

KKumaEngine::~KKumaEngine()
{
}

void KKumaEngine::Initialize()
{
}

void KKumaEngine::Shutdown()
{
}

void KKumaEngine::EngineTick(float DeltaTime)
{
}

void KKumaEngine::RequireEngineExit()
{
    bExitRequired = true;
}

bool KKumaEngine::IsEngineExitRequired() const
{
    return bExitRequired;
}
