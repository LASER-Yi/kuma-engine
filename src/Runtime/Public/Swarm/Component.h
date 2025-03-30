#pragma once

#include "Swarm/Definition.h"

namespace Swarm
{

/**
 * @brief Base class for all components in the swarm.
 */
struct FComponent
{
    virtual ~FComponent(){};

    Swarm::SignatureType Signature = Swarm::InvalidSignature;
    Swarm::SignatureType GetSignature() const { return Signature; }
};

} // namespace Swarm
