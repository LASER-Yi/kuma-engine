#pragma once

#include "CoreMinimal.h"
#include "Swarm/Definition.h"
#include "Swarm/Interfaces/Component.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <type_traits>

namespace Swarm
{

/**
 * @brief A dynamic array of components of a specific type.
 * @details This class is used to store components of a specific type in a
 * dynamic array. It provides methods to add, remove, and access components.
 */
struct FComponentArray
{
    FComponentArray() : FComponentArray(Swarm::InvalidType, 0) {}

    FComponentArray(Swarm::ComponentType Type, std::int32_t Size)
        : Type(Type), ComponentSize(Size), ContainerSize(0),
          ContainerCapacity(1)
    {
        Container = std::shared_ptr<std::byte>(static_cast<std::byte*>(
            std::malloc(ContainerCapacity * ComponentSize)
        ));
    }

    template <typename T, typename... Args>
    Swarm::ComponentIndex Add(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        assert(Type == T::GetType());
        assert(ComponentSize == sizeof(T));

        ContainerSize = ContainerSize + 1;

        if (ContainerSize > ContainerCapacity)
        {
            ContainerCapacity = ContainerCapacity * 2;

            // Reallocate the container
            std::byte* OldContainer = Container.get();
            Container = std::shared_ptr<std::byte>(static_cast<std::byte*>(
                std::realloc(OldContainer, ContainerCapacity * ComponentSize)
            ));
        }

        // Allocate space from the container pointer and initialize T
        Swarm::ComponentIndex NewIndex = ContainerSize - 1;

        T* NewComponent = reinterpret_cast<T*>(Container.get()) + NewIndex;
        new (NewComponent) T(std::forward<Args>(Arguments)...);

        return NewIndex;
    }

    template <typename T>
    T* GetItem(Swarm::ComponentIndex InIndex)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        assert(Type == T::GetType());
        assert(0 <= InIndex && InIndex < ContainerSize);

        return reinterpret_cast<T*>(Container.get()) + InIndex;
    }

    void Remove(Swarm::ComponentIndex InIndex)
    {
        assert(Type != Swarm::InvalidType);
        assert(0 <= InIndex && InIndex < ContainerSize);

        const size_t LastIndex = ContainerSize - 1;

        if (InIndex == LastIndex)
        {
            // If the last element is being removed, just reduce the size
            ContainerSize = ContainerSize - 1;
            return;
        }

        std::byte* RemoveTarget = static_cast<std::byte*>(Container.get()) +
                                  (InIndex * ComponentSize);
        std::byte* LastElement = static_cast<std::byte*>(Container.get()) +
                                 (LastIndex * ComponentSize);

        // Move the last element to the index of the removed element
        std::memcpy(RemoveTarget, LastElement, ComponentSize);
    }

public:
    std::size_t GetSize() const { return ContainerSize; }
    std::size_t GetCapacity() const { return ContainerCapacity; }

private:
    // Metadata
    Swarm::ComponentType Type;
    std::size_t ComponentSize;

private:
    std::shared_ptr<std::byte> Container;
    std::size_t ContainerSize;
    std::size_t ContainerCapacity;
};
} // namespace Swarm
