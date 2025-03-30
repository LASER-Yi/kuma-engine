#include "Kuma/Entities/KumaEntity.h"

#include "Kuma/Components/Transform.h"
#include "Kuma/Components/World.h"

FKumaEntity::FKumaEntity(Swarm::SignatureType InSignature)
    : Swarm::FEntity(InSignature)
{
    AddComponent<FWorldComponent>();
    AddComponent<FTransformComponent>();
}
