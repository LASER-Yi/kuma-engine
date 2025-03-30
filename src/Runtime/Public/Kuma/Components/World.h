#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaWorld.h"
#include <memory>

struct FWorldComponent : public Swarm::FComponent
{
    std::weak_ptr<FKumaWorld> World;
};
