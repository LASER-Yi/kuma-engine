#include "Kuma/Systems/CameraSystem.h"

#include "EntityQuery.h"

#include "Kuma/Components/CameraData.h"
#include "Kuma/Components/TransformData.h"

void KCameraSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FCameraData>(EComponentAccessMode::ReadWrite);
}

void KCameraSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    auto Renderer = GetEngine()->GetRenderer();

    Query.ForEach(
        Context,
        [&](const Swarm::FEntityQueryResult& Result)
        {
            const FTransformData* Transform =
                Result.GetComponent<FTransformData>();

            FCameraData* CameraData =
                Result.GetComponentReadWrite<FCameraData>();

            // TODO: Feed camera data to the renderer
        }
    );
}

void KCameraSystem::Shutdown() {}
