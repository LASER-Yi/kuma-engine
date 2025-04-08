#include "Kuma/Entities/KumaEntity.h"

#include "Kuma/Components/Transform.h"
#include "Kuma/Components/World.h"
#include "Swarm/EntityBase.h"

FKumaEntity::FKumaEntity(Swarm::FEntityInitializationContext& Context)
    : Swarm::FEntity(Context)
{
    Context.CreateDefaultComponent<FWorldComponent>();
    Context.CreateDefaultComponent<FMatrixComponent>();
}
