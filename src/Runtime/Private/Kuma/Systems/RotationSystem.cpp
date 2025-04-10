#include "Kuma/Systems/RotationSystem.h"

#include "Kuma/Components/RotationData.h"
#include "Kuma/Components/TransformData.h"

#include "Rotator.h"

void KRotationSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FRotationData>(EComponentAccessMode::ReadOnly);
    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadWrite);
}

void KRotationSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    using namespace Swarm;

    Query.ForEach(
        Context,
        [&](const FEntityQueryResult& Result)
        {
            const float DeltaTime = Context.DeltaTime;

            const FRotationData* RotationData =
                Result.GetComponent<FRotationData>();

            FTransformData* Transform =
                Result.GetComponentReadWrite<FTransformData>();

            Transform->LocalTransform.Rotation +=
                (RotationData->Rotation * Math::FDegrees(DeltaTime));
        }
    );
}

void KRotationSystem::Shutdown() {}
