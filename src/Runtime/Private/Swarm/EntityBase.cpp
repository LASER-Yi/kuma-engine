#include "Swarm/EntityBase.h"
#include "Swarm/Manager.h"

namespace Swarm
{

FEntityBase::FEntityBase()
{
    Index = Swarm::Manager::Get()->AllocateEntityIndex();
}

FEntityBase::~FEntityBase() { Swarm::Manager::Get()->RemoveEntity(this); }

Swarm::EntityIndex FEntityBase::GetIndex() const { return Index; }

} // namespace Swarm
