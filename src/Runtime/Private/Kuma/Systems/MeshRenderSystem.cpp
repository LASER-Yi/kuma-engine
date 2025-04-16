#include "Kuma/Systems/MeshRenderSystem.h"

#include "Engine/StaticMesh.h"
#include "EntityQuery.h"
#include "Kuma/Components/StaticMeshData.h"
#include "Kuma/Components/TransformData.h"
#include "Kuma/KumaEngine.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Shader.h"

#include <memory>

void KMeshRenderSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FStaticMeshData>(EComponentAccessMode::ReadWrite);

    const auto Renderer = GetEngine()->GetRenderer();
    const auto* Shader = Renderer->GetShaderManager();
    GlobalStateObject = Renderer->CreateStateObject(Shader->GetPrimitive());
}

void KMeshRenderSystem::Execute(const Swarm::FExecutionContext& Context)
{
    using namespace Swarm;

    auto Renderer = GetEngine()->GetRenderer();

    Query.ForEach(
        Context,
        [&](const FEntityQueryResult& Result)
        {
            FStaticMeshData* StaticMeshData =
                Result.GetComponentReadWrite<FStaticMeshData>();

            const FTransformData* TransformData =
                Result.GetComponent<FTransformData>();

            if (StaticMeshData->SceneProxy == nullptr)
            {
                const auto Proxy =
                    CreateSceneProxy(Renderer, TransformData, StaticMeshData);
                StaticMeshData->SceneProxy = Proxy;
                Renderer->SetPrimitive(Proxy);
            }

            StaticMeshData->SceneProxy->ComponentToWorld =
                TransformData->LocalToWorld;
        }
    );
}

void KMeshRenderSystem::Shutdown() { GlobalStateObject = nullptr; }

std::shared_ptr<FPrimitiveSceneProxy> KMeshRenderSystem::CreateSceneProxy(
    std::shared_ptr<KRenderer> Renderer, const FTransformData* TransformData,
    const FStaticMeshData* MeshData
) const
{
    const auto Mesh = MeshData->Mesh;
    if (Mesh == nullptr)
    {
        return nullptr;
    }

    auto SceneProxy = std::make_shared<FPrimitiveSceneProxy>();
    SceneProxy->ComponentToWorld = TransformData->LocalToWorld;
    SceneProxy->bStatic = TransformData->MovementMode == EMovementMode::Static;
    SceneProxy->Signature = MeshData->Signature;

    // TODO: Move those initialization to rendering thread
    SceneProxy->PipelineStateObject = GlobalStateObject;
    SceneProxy->SceneResource = Renderer->CreateSceneResource();
    SceneProxy->MeshResource = Renderer->CreateMesh(Mesh->Describe());

    return SceneProxy;
}
