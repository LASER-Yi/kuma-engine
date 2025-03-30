#include "Swarm/EntityBase.h"

namespace Swarm
{

FEntityBase::FEntityBase() : Index(Swarm::InvalidIndex) {}

void FEntityBase::Reset() { Index = Swarm::InvalidIndex; }

Swarm::EntityIndex FEntityBase::GetUnderlyingIndex() const { return Index; }

void FEntityBase::InternalSetUnderlyingIndex(Swarm::EntityIndex NewIndex)
{
    Index = NewIndex;
}

} // namespace Swarm
