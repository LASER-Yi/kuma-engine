#include "Kuma/Entities/KumaEntity.h"

#include "Kuma/Components/Transform.h"
#include "Kuma/Components/World.h"

FKumaEntity::FKumaEntity() : Swarm::FEntity()
{
    AddDefaultComponent<FWorldComponent>();
    AddDefaultComponent<FTransformComponent>();
}
