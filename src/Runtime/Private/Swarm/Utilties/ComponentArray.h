#pragma once

#include "CoreMinimal.h"
#include "Swarm/Interfaces/Component.h"

#include <cassert>

namespace Swarm
{

struct FComponentArray
{
    FComponentArray();

    FComponentArray(Swarm::ComponentType Type, std::int32_t Size)
        : ContainerType(Type), ComponentSize(Size)
    {
    }

    template <typename T, typename... Args>
    Swarm::ComponentIndex Add(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );

        assert(ContainerType == T::GetType());
        assert(ComponentSize == sizeof(T));

        T Component = T(std::forward<Args>(Arguments)...);

        // TODO: Store the component in a container
        // Components.push_back(Component);
        return Swarm::Invalid;
    }

    template <typename T>
    T& GetItem(Swarm::ComponentIndex InIndex)
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );

        assert(ContainerType == T::GetType());

        UNUSED_VAR(InIndex);

        // Get the component from the component manager
        assert(true && "GetItem not implemented");
    }

    void Remove(Swarm::ComponentIndex);

private:
    Swarm::ComponentType ContainerType;
    std::int32_t ComponentSize;
};
} // namespace Swarm
