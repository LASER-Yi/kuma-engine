#include "Swarm/Entity.h"
#include "Swarm/SwarmDefine.h"

namespace Swarm
{

FEntity::FEntity(Swarm::EntityIndex InIndex) : EntityIndex(InIndex) {}

void FEntity::Reset() { EntityIndex = Swarm::Invalid; }

} // namespace Swarm
