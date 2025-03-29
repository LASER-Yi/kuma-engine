#include "CoreMinimal.h"
#include "Kuma/Components/Transform.h"
#include "Swarm/SwarmManager.h"

#include "Kuma/Entities/KumaEntity.h"

FKumaEntity::FKumaEntity(Swarm::EntityIndex InIndex) : Swarm::FEntity(InIndex)
{
    Swarm::KManager::Get()->AddComponent<FTransformComponent>(*this);
}
