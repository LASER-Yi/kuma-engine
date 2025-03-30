#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Components/World.h"
#include "Kuma/Components/WorldEntity.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Swarm/Entity.h"

FKumaWorld::FKumaWorld() : Swarm::FEntity()
{
    AddComponent<FWorldEntityComponent>();
}

void FKumaWorld::AddToWorld(std::shared_ptr<FKumaEntity> InEntity)
{
    if (InEntity == nullptr)
    {
        return;
    }

    // Update world entity component (self)
    {
        FWorldEntityComponent* WorldEntity =
            GetComponent<FWorldEntityComponent>();
        assert(WorldEntity != nullptr);

        WorldEntity->Entities.insert(InEntity);
    }

    // Update world component (InEntity)
    {
        FWorldComponent* WorldComponent =
            InEntity->GetComponent<FWorldComponent>();
        assert(WorldComponent != nullptr);

        WorldComponent->World = GetShared<FKumaWorld>();
    }
}
