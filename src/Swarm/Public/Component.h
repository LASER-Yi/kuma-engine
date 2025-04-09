#pragma once

#include "Interfaces/Identifiable.h"

namespace Swarm
{

/**
 * @brief Base class for all components in the swarm.
 */
struct FComponent : public IIdentifiable
{
    FComponent() = default;

    FComponent(const FComponent&) = delete;
    FComponent& operator=(const FComponent&) = delete;
    FComponent(FComponent&&) = delete;
    FComponent& operator=(FComponent&&) = delete;
};

} // namespace Swarm
