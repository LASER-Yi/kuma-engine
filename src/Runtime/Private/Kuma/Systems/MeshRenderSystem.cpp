#include "Kuma/Systems/MeshRenderSystem.h"

#include <memory>

#include "Engine/StaticMesh.h"
#include "EntityQuery.h"
#include "Kuma/Components/StaticMeshData.h"
#include "Kuma/Components/TransformData.h"
#include "Kuma/KumaEngine.h"
#include "Matrix.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Shader.h"

void KMeshRenderSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FStaticMeshData>(EComponentAccessMode::ReadWrite);

    const auto Renderer = GetEngine()->GetRenderer();
    const auto* Shader = Renderer->GetShaderManager();
    GlobalStateObject = Renderer->CreateStateObject(Shader->GetPrimitive());
}

void KMeshRenderSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    using namespace Swarm;

    auto Renderer = GetEngine()->GetRenderer();

    Query.ForEach(
        Context,
        [&](const FEntityQueryResult& Result)
        {
            FStaticMeshData* StaticMeshData =
                Result.GetComponentReadWrite<FStaticMeshData>();

            if (StaticMeshData->SceneProxy == nullptr)
            {
                const auto SceneProxy = CreateSceneProxy(StaticMeshData);
                StaticMeshData->SceneProxy = SceneProxy;
                Renderer->Enqueue(SceneProxy);
            }

            const FTransformData* Transform =
                Result.GetComponent<FTransformData>();

            StaticMeshData->SceneProxy->ComponentToWorld =
                Transform->LocalTransform.ToMatrix();
        }
    );
}

void KMeshRenderSystem::Shutdown() { GlobalStateObject = nullptr; }

std::shared_ptr<FSceneProxy> KMeshRenderSystem::CreateSceneProxy(
    const FStaticMeshData* Comp
) const
{
    if (Comp == nullptr)
    {
        return nullptr;
    }

    if (Comp->Mesh == nullptr)
    {
        return nullptr;
    }

    auto Renderer = GetEngine()->GetRenderer();

    auto SceneProxy = std::make_shared<FSceneProxy>();

    SceneProxy->ComponentToWorld = Math::FMatrix::Identity;

    SceneProxy->PipelineStateObject = GlobalStateObject;
    SceneProxy->SceneBuffer = Renderer->CreateSceneResource();
    SceneProxy->MeshResource = Renderer->CreateMesh(Comp->Mesh->Describe());

    return SceneProxy;
}
