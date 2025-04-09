#include "Kuma/KumaEngine.h"

#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"

#include "Kuma/Components/StaticMeshData.h"
#include "Kuma/Components/TransformData.h"

#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Systems/CameraSystem.h"
#include "Kuma/Systems/MeshRenderSystem.h"
#include "Kuma/Systems/RotationSystem.h"
#include "Manager.h"

void KKumaEngine::Initialize(const FEngineInitializationContext& Context)
{
    KEngine::Initialize(Context);
    Swarm::Manager::Get()->AddSystem<KMeshRenderSystem>();
    Swarm::Manager::Get()->AddSystem<KRotationSystem>();
    Swarm::Manager::Get()->AddSystem<KCameraSystem>();

    CurrentWorld = Swarm::Manager::Get()->MakeEntity<FKumaWorld>();

    {
        auto Entity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        Entity->AddComponent<FStaticMeshData>(FStaticMesh::Cube());
        FTransformData* Transform = Entity->GetComponent<FTransformData>();

        Transform->LocalTransform.Translation.X = 10.0;

        CurrentWorld->AddToWorld(Entity);
    }

    {
        auto AnotherEntity = Swarm::Manager::Get()->MakeEntity<FKumaEntity>();
        AnotherEntity->AddComponent<FStaticMeshData>(FStaticMesh::Cube());
        FTransformData* Transform =
            AnotherEntity->GetComponent<FTransformData>();

        Transform->LocalTransform.Translation = {12.0, 2.0, 2.0};

        CurrentWorld->AddToWorld(AnotherEntity);
    }
}

void KKumaEngine::Shutdown()
{
    CurrentWorld = nullptr;

    KEngine::Shutdown();
}
