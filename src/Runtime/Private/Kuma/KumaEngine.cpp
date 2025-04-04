#include "Kuma/KumaEngine.h"
#include "Engine/Engine.h"
#include "Kuma/Components/Primitive.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/PrimitiveSystem.h"
#include "Swarm/Manager.h"
#include "Vector.h"

void KKumaEngine::Initialize()
{
    KEngine::Initialize();
    Swarm::Manager::Get()->AddSystem<KPrimitiveSystem>();
    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    std::vector<FVector> Vertex;
    Vertex.push_back({0.0, 0.0, 0.0});
    Vertex.push_back({0.0, 0.5, 0.0});
    Vertex.push_back({0.5, 0.0, 0.0});

    auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    Entity->AddComponent<FPrimitiveComponent>(Vertex);

    CurrentWorld->AddToWorld(Entity);

    for (auto& AnotherVertex : Vertex)
    {
        AnotherVertex.X -= 0.6;
    }

    auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
    AnotherEntity->AddComponent<FPrimitiveComponent>(Vertex);

    CurrentWorld->AddToWorld(AnotherEntity);
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;
    
    KEngine::Shutdown();
}
