#include "Swarm/EntityBase.h"
#include "Swarm/Manager.h"

namespace Swarm
{

FEntityBase::FEntityBase() : IIdentifiable() {}
FEntityBase::~FEntityBase() { Swarm::Manager::Get()->RemoveEntity(this); }

} // namespace Swarm
