#pragma once

#include "CoreMinimal.h"
#include "Swarm/Interfaces/Component.h"
#include "Swarm/SwarmDefine.h"

#include <cassert>

namespace Swarm
{

struct FEntity
{
    FEntity(Swarm::EntityIndex InIndex);
    ~FEntity() = default;

    FEntity(const FEntity&) = default;
    FEntity& operator=(const FEntity&) = default;

    FEntity(FEntity&&) = delete;
    FEntity& operator=(FEntity&&) = delete;

    void Reset();

    template <typename T>
    const T* GetComponent() const
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from ISwarmComponent"
        );

        // Get the component from the component manager
        assert(true && "GetComponent not implemented");
    }

    template <typename T>
    T* AddComponent()
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from ISwarmComponent"
        );

        // Add the component to the component manager
        assert(true && "AddComponent not implemented");
    }

    template <typename T>
    void RemoveComponent()
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from ISwarmComponent"
        );

        // Remove the component from the component manager
        assert(true && "RemoveComponent not implemented");
    }

    Swarm::EntityIndex GetUnderlyingIndex() const { return EntityIndex; }

public:
    Swarm::EntityIndex EntityIndex = Swarm::Invalid;
};

} // namespace Swarm
