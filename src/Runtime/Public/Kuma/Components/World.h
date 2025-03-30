#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaWorld.h"
#include <memory>

struct FWorldComponent : public Swarm::IComponent<FWorldComponent>
{
    std::weak_ptr<FKumaWorld> World;
};
