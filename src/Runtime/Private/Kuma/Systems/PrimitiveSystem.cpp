#include "Kuma/Systems/PrimitiveSystem.h"

#include <memory>

#include "Engine/StaticMesh.h"
#include "EntityQuery.h"
#include "Kuma/Components/Primitive.h"
#include "Kuma/Components/Transform.h"
#include "Kuma/KumaEngine.h"
#include "Matrix.h"
#include "Renderer.h"
#include "Rotator.h"
#include "SceneProxy.h"
#include "Shader.h"

void KPrimitiveSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformComponent>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FPrimitiveComponent>(EComponentAccessMode::ReadWrite);

    const auto Renderer = GetEngine()->GetRenderer();
    const auto* Shader = Renderer->GetShaderManager();
    GlobalStateObject = Renderer->CreateStateObject(Shader->GetPrimitive());
}

void KPrimitiveSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    using namespace Swarm;

    auto Renderer = GetEngine()->GetRenderer();

    Query.ForEach(
        Context,
        [&](const FEntityQueryResult& Result)
        {
            FPrimitiveComponent* Primitive =
                Result.GetComponentReadWrite<FPrimitiveComponent>();

            if (Primitive->SceneProxy == nullptr)
            {
                const auto SceneProxy = CreateSceneProxy(Primitive);
                Primitive->SceneProxy = SceneProxy;
                Renderer->Enqueue(SceneProxy);
            }

            const FTransformComponent* Transform =
                Result.GetComponent<FTransformComponent>();

            Primitive->SceneProxy->ComponentToWorld =
                Transform->LocalTransform.ToMatrix();
        }
    );
}

void KPrimitiveSystem::Shutdown() { GlobalStateObject = nullptr; }

std::shared_ptr<FSceneProxy> KPrimitiveSystem::CreateSceneProxy(
    const FPrimitiveComponent* Comp
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
