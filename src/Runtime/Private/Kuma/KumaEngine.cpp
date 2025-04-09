#include "Kuma/KumaEngine.h"

#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

#include "Kuma/Components/Primitive.h"
#include "Kuma/Components/Transform.h"

#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/PrimitiveSystem.h"
#include "Kuma/Systems/RotationSystem.h"
#include "Manager.h"

void KKumaEngine::Initialize(const FEngineInitializationContext& Context)
{
    KEngine::Initialize(Context);
    Swarm::Manager::Get()->AddSystem<KPrimitiveSystem>();
    Swarm::Manager::Get()->AddSystem<KRotationSystem>();

    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    {
        auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        Entity->AddComponent<FPrimitiveComponent>(FStaticMesh::Cube());
        FTransformComponent* Transform =
            Entity->GetComponent<FTransformComponent>();

        Transform->LocalTransform.Translation.Z = -10.0;

        CurrentWorld->AddToWorld(Entity);
    }

    {
        auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        AnotherEntity->AddComponent<FPrimitiveComponent>(FStaticMesh::Cube());
        FTransformComponent* Transform =
            AnotherEntity->GetComponent<FTransformComponent>();

        Transform->LocalTransform.Translation.X = 2.0;
        Transform->LocalTransform.Translation.Z = -5.0;

        CurrentWorld->AddToWorld(AnotherEntity);
    }
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;

    KEngine::Shutdown();
}
