#pragma once

#include "CoreMinimal.h"
#include "Swarm/Definition.h"

namespace Swarm
{

struct FEntity
{
    FEntity(Swarm::EntityIndex InIndex);
    ~FEntity() = default;

    FEntity(const FEntity&) = default;
    FEntity& operator=(const FEntity&) = default;

    FEntity(FEntity&&) = delete;
    FEntity& operator=(FEntity&&) = delete;

    void Reset();

    Swarm::EntityIndex GetUnderlyingIndex() const { return EntityIndex; }

public:
    Swarm::EntityIndex EntityIndex = Swarm::Invalid;
};

} // namespace Swarm
