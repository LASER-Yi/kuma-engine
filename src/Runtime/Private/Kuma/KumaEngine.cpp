#include "Kuma/KumaEngine.h"
#include "Engine/Engine.h"
#include "Kuma/Components/Primitive.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/PrimitiveSystem.h"
#include "Swarm/Manager.h"

void KKumaEngine::Initialize()
{
    KEngine::Initialize();
    Swarm::Manager::Get()->AddSystem<KPrimitiveSystem>();
    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    Entity->AddComponent<FPrimitiveComponent>();

    CurrentWorld->AddToWorld(Entity);
}

void KKumaEngine::Shutdown()
{
    KEngine::Shutdown();
    CurrentWorld.reset();
}
