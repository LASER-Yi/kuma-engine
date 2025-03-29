#pragma once

#include "Core/CoreMinimal.h"
#include "Swarm/SwarmDefine.h"

#include <type_traits>

namespace Swarm
{

class IComponent
{
    template <typename T> static Swarm::ComponentType GetType()
    {
        static_assert(std::is_base_of<IComponent, T>::value,
                      "T must be derived from ISwarmComponent");

        return T::GetType();
    }
};

} // namespace Swarm
