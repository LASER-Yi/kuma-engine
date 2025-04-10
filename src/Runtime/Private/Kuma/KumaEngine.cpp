#include "Kuma/KumaEngine.h"

#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

#include "Kuma/Components/CameraData.h"
#include "Kuma/Components/RotationData.h"
#include "Kuma/Components/StaticMeshData.h"
#include "Kuma/Components/TransformData.h"

#include "Kuma/Entities/CameraEntity.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/CameraRenderSystem.h"
#include "Kuma/Systems/MeshRenderSystem.h"
#include "Kuma/Systems/RotationSystem.h"
#include "Kuma/Systems/WorldHierarchicalSystem.h"
#include "Manager.h"

void KKumaEngine::Initialize(const FEngineInitializationContext& Context)
{
    KEngine::Initialize(Context);
    Swarm::Manager::Get()->AddSystem<KWorldHierarchicalSystem>();
    Swarm::Manager::Get()->AddSystem<KMeshRenderSystem>();
    Swarm::Manager::Get()->AddSystem<KRotationSystem>();
    Swarm::Manager::Get()->AddSystem<KCameraRenderSystem>();

    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    {
        auto Camera = Swarm::Manager::Get()->MakeEntity<FCameraEntity>();
        FCameraData* CameraData = Camera->GetComponent<FCameraData>();
        CameraData->bActive = true;

        FTransformData* Transform = Camera->GetComponent<FTransformData>();
        Transform->LocalTransform.Translation.X = -10.0;

        CurrentWorld->AddToWorld(Camera);
    }

    {
        auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        Entity->AddComponent<FStaticMeshData>(FStaticMesh::Cube());
        FTransformData* Transform = Entity->GetComponent<FTransformData>();

        Entity->AddComponent<FRotationData>(FRotator(0.0, 15.0, 10.0));

        CurrentWorld->AddToWorld(Entity);
    }

    {
        auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        AnotherEntity->AddComponent<FStaticMeshData>(FStaticMesh::Cube());
        FTransformData* Transform =
            AnotherEntity->GetComponent<FTransformData>();

        Transform->LocalTransform.Translation = {.0, 2.0, 2.0};

        CurrentWorld->AddToWorld(AnotherEntity);
    }
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;

    KEngine::Shutdown();
}
