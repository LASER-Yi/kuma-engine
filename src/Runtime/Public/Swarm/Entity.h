#pragma once

#include "CoreMinimal.h"
#include "Swarm/Definition.h"

namespace Swarm
{

/**
 * @brief Represents an entity in the swarm system.
 * @details This class is used to represent an entity in the swarm system. It
 * contains an index that is used to identify the entity in the system.
 */
struct FEntity
{
    FEntity(Swarm::EntityIndex InIndex);
    ~FEntity() = default;

    FEntity(const FEntity&) = default;
    FEntity& operator=(const FEntity&) = default;

    FEntity(FEntity&&) = default;
    FEntity& operator=(FEntity&&) = default;

    /**
     * @brief Reset the entity to invalid state.
     * @details This function resets the entity to its initial state.
     * Please noted that the entity will not be removed by calling this
     * function.
     */
    void Reset();

    /**
     * @brief Get the index of the entity.
     * @return The index of the entity.
     */
    Swarm::EntityIndex GetUnderlyingIndex() const { return EntityIndex; }

public:
    Swarm::EntityIndex EntityIndex = Swarm::InvalidIndex;
};

} // namespace Swarm
