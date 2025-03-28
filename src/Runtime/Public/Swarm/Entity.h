#pragma once

#include "CoreMinimal.h"

namespace Swarm
{

/**
 * @brief Represents an entity in the swarm system.
 * @details This class is used to represent an entity in the swarm system. It
 * contains an index that is used to identify the entity in the system.
 */
struct FEntity
{
    FEntity();
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
    Swarm::EntityIndex GetUnderlyingIndex() const;

    /**
     * @brief Set the index of the entity (internal use only)
     * @param NewIndex The new index of this entity
     */
    void InternalSetUnderlyingIndex(Swarm::EntityIndex NewIndex);

public:
    Swarm::EntityIndex Index = Swarm::InvalidIndex;
};

} // namespace Swarm
