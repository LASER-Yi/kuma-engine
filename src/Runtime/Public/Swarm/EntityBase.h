#pragma once

#include "Swarm/Definition.h"
#include "Swarm/Interfaces/Identifiable.h"

#include <memory>
#include <unordered_map>
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

    // TODO: Refactor and make sizeof(FEntityBase) == sizeof(int64)
    std::unordered_map<Swarm::ClassHashType, Swarm::SignatureType>
        DefaultComponents;
};

} // namespace Swarm
