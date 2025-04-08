#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaEntity.h"

struct FKumaWorld : public Swarm::FEntity
{
    FKumaWorld(Swarm::FEntityInitializationContext& Context);

    void AddToWorld(std::shared_ptr<FKumaEntity> InEntity);
};
