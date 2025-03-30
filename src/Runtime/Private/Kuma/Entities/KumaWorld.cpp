#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Components/World.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Swarm/Entity.h"

FKumaWorld::FKumaWorld() : Swarm::FEntity() {}

void FKumaWorld::AddToWorld(FKumaEntity* InEntity)
{
    if (InEntity == nullptr)
    {
        return;
    }

    FWorldComponent* WorldComponent = GetComponent<FWorldComponent>();
    assert(WorldComponent != nullptr);

    WorldComponent->World = *this;
}
