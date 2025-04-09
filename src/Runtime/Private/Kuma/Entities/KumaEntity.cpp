#include "Kuma/Entities/KumaEntity.h"

#include "EntityBase.h"
#include "Kuma/Components/TransformData.h"
#include "Kuma/Components/WorldData.h"

FKumaEntity::FKumaEntity(Swarm::FEntityInitializationContext& Context)
    : Swarm::FEntity(Context)
{
    Context.CreateDefaultComponent<FWorldData>();
    Context.CreateDefaultComponent<FTransformData>();
}
