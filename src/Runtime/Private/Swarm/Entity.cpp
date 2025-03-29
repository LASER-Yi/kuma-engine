#include "Swarm/Entity.h"
#include "Swarm/Definition.h"

namespace Swarm
{

FEntity::FEntity() : Index(Swarm::InvalidIndex) {}

void FEntity::Reset() { Index = Swarm::InvalidIndex; }

Swarm::EntityIndex FEntity::GetUnderlyingIndex() const { return Index; }

void FEntity::InternalSetUnderlyingIndex(Swarm::EntityIndex NewIndex)
{
    Index = NewIndex;
}

} // namespace Swarm
