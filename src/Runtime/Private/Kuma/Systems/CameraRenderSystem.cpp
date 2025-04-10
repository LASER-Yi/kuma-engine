#include "Kuma/Systems/CameraRenderSystem.h"

#include "EntityQuery.h"
#include "Renderer.h"
#include "SceneProxy.h"

#include "Kuma/Components/CameraData.h"
#include "Kuma/Components/TransformData.h"
#include <memory>

void KCameraRenderSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FCameraData>(EComponentAccessMode::ReadWrite);
}

void KCameraRenderSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    auto Renderer = GetEngine()->GetRenderer();

    Query.ForEach(
        Context,
        [&](const Swarm::FEntityQueryResult& Result)
        {
            FCameraData* CameraData =
                Result.GetComponentReadWrite<FCameraData>();

            if (CameraData->SceneProxy == nullptr)
            {
                auto SceneProxy = CreateSceneProxy(CameraData);
                CameraData->SceneProxy = SceneProxy;
            }

            const FTransformData* Transform =
                Result.GetComponent<FTransformData>();

            std::shared_ptr<FCameraSceneProxy> CameraProxy =
                CameraData->SceneProxy;

            CameraProxy->FieldOfView = CameraData->FieldOfView;
            CameraProxy->NearClip = CameraData->NearClip;
            CameraProxy->FarClip = CameraData->FarClip;
            CameraProxy->ComponentToWorld = Transform->LocalToWorld;

            if (CameraData->bActive)
            {
                Renderer->SetCamera(CameraProxy);
            }
        }
    );
}

void KCameraRenderSystem::Shutdown() {}

std::shared_ptr<FCameraSceneProxy> KCameraRenderSystem::CreateSceneProxy(
    const FCameraData* InData
) const
{
    if (InData == nullptr)
    {
        return nullptr;
    }

    auto Renderer = GetEngine()->GetRenderer();

    auto SceneProxy = std::make_shared<FCameraSceneProxy>();
    SceneProxy->Signature = InData->Signature;
    SceneProxy->ComponentToWorld = Math::FMatrix::Identity;

    return SceneProxy;
}
