#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Swarm/Definition.h"
#include "Swarm/Interfaces/Component.h"

struct FWorldComponent : public Swarm::IComponent<FWorldComponent>
{
    FKumaWorld World = Swarm::InvalidIndex;
};
