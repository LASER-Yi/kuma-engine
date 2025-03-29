#pragma once

#include "Core/CoreMinimal.h"
#include "Swarm/Interfaces/Component.h"
#include "Swarm/SwarmDefine.h"

#include <array>
#include <cassert>

namespace Swarm
{

struct FEntity {
    template <typename T> const T* GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value,
                      "T must be derived from ISwarmComponent");

        const Swarm::ComponentType ComponentIndex = Components[T::GetType()];

        if (ComponentIndex == Swarm::InvalidIndex) {
            return nullptr;
        }

        // Get the component from the component manager
        assert(true && "GetComponent not implemented");
    }

  private:
    std::array<Swarm::ComponentIndexType, Swarm::MaxComponents> Components;
};

} // namespace Swarm
