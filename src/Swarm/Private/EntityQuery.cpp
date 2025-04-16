#include "EntityQuery.h"

#include <vector>

namespace Swarm
{

FEntityQueryResult::FEntityQueryResult(
    SignatureType InEntity, const FEntityQuery* InInstigator,
    const FExecutionContext* InContext
)
    : Entity(InEntity), Instigator(InInstigator), Context(InContext)
{
}

void FEntityQuery::ForEach(
    const FExecutionContext& Context, FEntityQuery::Function&& Func
) const
{
    Manager* SwarmMgr = Context.Manager;

    std::vector<SignatureType> RequireComponents;
    for (const auto& [ComponentType, AccessType] : Requirements)
    {
        RequireComponents.push_back(ComponentType);
    }

    std::vector<SignatureType> Entities;
    SwarmMgr->FilterEntityByComponents(Entities, RequireComponents);

    for (SignatureType Entity : Entities)
    {
        const FEntityQueryResult Result(Entity, this, &Context);

        Func(Result);
    }
}

} // namespace Swarm
