#include "Kuma/Entities/KumaWorld.h"
#include "Kuma/Components/WorldData.h"
#include "Kuma/Components/WorldEntity.h"
#include "Kuma/Entities/KumaEntity.h"

FKumaWorld::FKumaWorld(Swarm::FEntityInitializationContext& Context)
    : Swarm::FEntity(Context)
{
    Context.CreateDefaultComponent<FWorldEntityComponent>();
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
        FWorldData* WorldData = InEntity->GetComponent<FWorldData>();
        assert(WorldData != nullptr);

        WorldData->AssociatedWorld = Signature;
    }
}
