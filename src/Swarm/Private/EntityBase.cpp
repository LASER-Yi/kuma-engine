#include "EntityBase.h"
#include "Manager.h"

namespace Swarm
{

FEntityBase::FEntityBase() : IIdentifiable() {}
FEntityBase::~FEntityBase() { Swarm::Manager::Get()->RemoveEntity(this); }

} // namespace Swarm
