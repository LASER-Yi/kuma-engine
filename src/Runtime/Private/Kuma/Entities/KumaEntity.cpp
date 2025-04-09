#include "Kuma/Entities/KumaEntity.h"

#include "EntityBase.h"
#include "Kuma/Components/TransformData.h"
#include "Kuma/Components/World.h"

FKumaEntity::FKumaEntity(Swarm::FEntityInitializationContext& Context)
    : Swarm::FEntity(Context)
{
    Context.CreateDefaultComponent<FWorldComponent>();
    Context.CreateDefaultComponent<FTransformData>();
}
