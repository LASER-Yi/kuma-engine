#pragma once

#include "Interfaces/Identifiable.h"

#include <memory>

namespace Swarm
{

/**
 * @brief Base class of an entity in the swarm system. Mainly use for
 * interacting with the swarm manager
 * @details This class is used to represent an entity in the swarm system. It
 * contains an index that is used to identify the entity in the system.
 */
struct FEntityBase : public IIdentifiable,
                     public std::enable_shared_from_this<FEntityBase>
{
    FEntityBase();
    virtual ~FEntityBase();

    FEntityBase(const FEntityBase&) = delete;
    FEntityBase& operator=(const FEntityBase&) = delete;

    FEntityBase(FEntityBase&&) = default;
    FEntityBase& operator=(FEntityBase&&) = default;
};

} // namespace Swarm
