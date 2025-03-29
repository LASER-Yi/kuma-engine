#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaWorld.h"

struct FWorldComponent : public Swarm::IComponent<FWorldComponent>
{
    FKumaWorld World;
};
