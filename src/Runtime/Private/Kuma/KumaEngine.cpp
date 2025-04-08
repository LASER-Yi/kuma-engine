#include "Kuma/KumaEngine.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Kuma/Components/Primitive.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/PrimitiveSystem.h"
#include "Swarm/Manager.h"

void KKumaEngine::Initialize(const FEngineInitializationContext& Context)
{
    KEngine::Initialize(Context);
    Swarm::Manager::Get()->AddSystem<KPrimitiveSystem>();
    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    Entity->AddComponent<FPrimitiveComponent>(FStaticMesh::Cube());

    CurrentWorld->AddToWorld(Entity);

    // for (auto& AnotherVertex : Vertex)
    // {
    //     AnotherVertex.X -= 0.6;
    // }

    // auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    // AnotherEntity->AddComponent<FPrimitiveComponent>(Vertex);

    // CurrentWorld->AddToWorld(AnotherEntity);
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;

    KEngine::Shutdown();
}
