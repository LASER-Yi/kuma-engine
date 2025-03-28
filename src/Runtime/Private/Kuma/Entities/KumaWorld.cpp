#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Components/World.h"
#include "Kuma/Entities/KumaEntity.h"

FKumaWorld::FKumaWorld() : Swarm::FEntity() {}

void FKumaWorld::AddToWorld(FKumaEntity* InEntity)
{
    if (InEntity == nullptr)
    {
        return;
    }

    Swarm::Manager* Manager = Swarm::Manager::Get();

    FWorldComponent* WorldComponent =
        Manager->GetComponent<FWorldComponent>(*InEntity);
    assert(WorldComponent != nullptr);

    WorldComponent->World = *this;
}
