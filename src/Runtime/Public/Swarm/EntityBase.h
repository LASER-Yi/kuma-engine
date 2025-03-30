#pragma once

#include <memory>
namespace Swarm
{

/**
 * @brief Base class of an entity in the swarm system. Mainly use for
 * interacting with the swarm manager
 * @details This class is used to represent an entity in the swarm system. It
 * contains an index that is used to identify the entity in the system.
 */
struct FEntityBase : public std::enable_shared_from_this<FEntityBase>
{
    FEntityBase();
    virtual ~FEntityBase();

    FEntityBase(const FEntityBase&) = delete;
    FEntityBase& operator=(const FEntityBase&) = delete;

    FEntityBase(FEntityBase&&) = default;
    FEntityBase& operator=(FEntityBase&&) = default;

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

private:
    Swarm::EntityIndex Index = Swarm::InvalidIndex;
};

} // namespace Swarm
