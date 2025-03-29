#include "Kuma/Entities/KumaEntity.h"

#include "Kuma/Components/Transform.h"
#include "Kuma/Components/World.h"

FKumaEntity::FKumaEntity() : Swarm::FEntity()
{
    Swarm::Manager* Manager = Swarm::Manager::Get();

    Manager->AddComponent<FWorldComponent>(*this);
    Manager->AddComponent<FTransformComponent>(*this);
}
