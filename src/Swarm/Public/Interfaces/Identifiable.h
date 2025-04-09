#pragma once

#include "Definition.h"

namespace Swarm
{

struct IIdentifiable
{
    IIdentifiable() : Signature(Swarm::InvalidSignature) {}
    virtual ~IIdentifiable() { Signature = Swarm::InvalidSignature; }

    bool IsValid() const { return Signature != Swarm::InvalidSignature; }

    /**
     * @brief The signature of this structure.
     */
    Swarm::SignatureType Signature = Swarm::InvalidSignature;
};

} // namespace Swarm
