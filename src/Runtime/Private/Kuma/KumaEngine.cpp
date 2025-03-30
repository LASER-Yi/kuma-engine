#include "Kuma/KumaEngine.h"
#include "Engine/Engine.h"
#include "Kuma/Entities/KumaWorld.h"

void KKumaEngine::Initialize()
{
    KEngine::Initialize();
    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();
}

void KKumaEngine::Shutdown()
{
    KEngine::Shutdown();
    CurrentWorld.reset();
}
