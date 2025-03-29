#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Swarm/Entity.h"

struct FKumaWorld : public Swarm::FEntity
{
    FKumaWorld();

    void AddToWorld(FKumaEntity* InEntity);
};
