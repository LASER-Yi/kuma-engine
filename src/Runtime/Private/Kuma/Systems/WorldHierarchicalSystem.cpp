#include "Kuma/Systems/WorldHierarchicalSystem.h"

#include "EntityQuery.h"
#include "Kuma/Components/TransformData.h"

void KWorldHierarchicalSystem::Initialize()
{
    using namespace Swarm;

    Query.AddRequirement<FTransformData>(EComponentAccessMode::ReadWrite);
}

void KWorldHierarchicalSystem::Execute(const Swarm::FExecutionContext& Context)
{
    Query.ForEach(
        Context,
        [](const Swarm::FEntityQueryResult& Result)
        {
            FTransformData* TransformData =
                Result.GetComponentReadWrite<FTransformData>();

            // TODO: Hierarchical
            TransformData->LocalToWorld =
                TransformData->LocalTransform.ToMatrix();
        }
    );
}
