#include "EntityQuery.h"
#include "SystemUpdateContext.h"

namespace Swarm
{

void FEntityQuery::ForEach(
    const FSystemUpdateContext& Context, FEntityQuery::Function&& Func
) const
{
}

} // namespace Swarm
