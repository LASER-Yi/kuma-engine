#include "Swarm/EntityBase.h"
#include "Swarm/Manager.h"

namespace Swarm
{

FEntityBase::FEntityBase() : Index(Swarm::InvalidIndex) {}

FEntityBase::~FEntityBase() { Swarm::Manager::Get()->RemoveEntity(this); }

Swarm::EntityIndex FEntityBase::GetUnderlyingIndex() const { return Index; }

void FEntityBase::InternalSetUnderlyingIndex(Swarm::EntityIndex NewIndex)
{
    Index = NewIndex;
}

} // namespace Swarm
