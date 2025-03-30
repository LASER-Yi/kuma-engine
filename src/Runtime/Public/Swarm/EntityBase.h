#pragma once

#include "Swarm/Definition.h"
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
    FEntityBase(Swarm::SignatureType Signature);
    virtual ~FEntityBase();

    FEntityBase(const FEntityBase&) = delete;
    FEntityBase& operator=(const FEntityBase&) = delete;

    FEntityBase(FEntityBase&&) = default;
    FEntityBase& operator=(FEntityBase&&) = default;

    /**
     * @brief Get the signature of the entity.
     * @return The signature of the entity.
     */
    Swarm::SignatureType GetSignature() const;

private:
    Swarm::SignatureType Signature = Swarm::InvalidSignature;
};

} // namespace Swarm
