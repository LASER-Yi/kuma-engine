#pragma once

#include "CoreMinimal.h"
#include <typeinfo>

namespace Swarm
{

/**
 * @brief Base class for all components in the swarm.
 * @tparam T Type of the derived component.
 *
 * This class provides a static method to get the type of the component.
 */
template <typename T>
class IComponent
{
public:
    /**
     * @brief Get the type of the component.
     * @return The type of the component as a Swarm::ComponentType.
     */
    static constexpr Swarm::ComponentType GetType()
    {
        return typeid(T).hash_code();
    }
};

} // namespace Swarm
