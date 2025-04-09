#pragma once

#include "CoreMinimal.h"
#include "Kuma/Entities/KumaEntity.h"

#include <memory>
#include <set>

struct FWorldEntityData : public Swarm::FComponent
{
    std::set<std::shared_ptr<FKumaEntity>> Entities;
};
