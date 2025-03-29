#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Swarm/Definition.h"
#include "Swarm/Entity.h"

struct FKumaWorld : public Swarm::FEntity
{
    FKumaWorld(Swarm::EntityIndex InIndex);

    void AddToWorld(FKumaEntity* InEntity);
};
