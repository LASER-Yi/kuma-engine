#include "Kuma/Systems/RotationSystem.h"
#include "Kuma/Components/Transform.h"
#include "Rotator.h"

void KRotationSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformComponent>(EComponentAccessMode::ReadWrite);
}

void KRotationSystem::Execute(const Swarm::FSystemUpdateContext& Context)
{
    using namespace Swarm;

    Query.ForEach(
        Context,
        [&](const FEntityQueryResult& Result)
        {
            const float DeltaTime = Context.DeltaTime;

            FTransformComponent* Transform =
                Result.GetComponentReadWrite<FTransformComponent>();

            Transform->LocalTransform.Rotation.Pitch +=
                Math::FDegrees(DeltaTime * 10.0f);

            Transform->LocalTransform.Rotation.Roll +=
                Math::FDegrees(DeltaTime * 15.0f);
        }
    );
}

void KRotationSystem::Shutdown() {}
