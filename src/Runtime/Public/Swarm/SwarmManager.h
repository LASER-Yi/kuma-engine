#pragma once

#include "CoreMinimal.h"
#include "Swarm/Interfaces/Component.h"
#include "Swarm/SwarmDefine.h"

#include <cassert>
#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "Swarm/Entity.h"
#include "Swarm/Interfaces/System.h"

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

class Manager final
{
public:
    Manager();
    ~Manager();

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Update(float DeltaTime);

    template <typename T>
    T MakeEntity()
    {
        static_assert(
            std::is_base_of<FEntity, T>::value, "T must be derived from FEntity"
        );

        static_assert(
            sizeof(T) == sizeof(FEntity), "T must be the same size as FEntity"
        );

        if (FreeEntityIndices.empty() == false)
        {
            Swarm::EntityIndex NextIndex = FreeEntityIndices.front();
            T Entity(NextIndex);
            FreeEntityIndices.pop();

            return Entity;
        }
        else
        {
            T Entity(NextEntityIndex);
            ++NextEntityIndex;

            assert(
                NextEntityIndex < std::numeric_limits<Swarm::EntityIndex>::max()
            );

            return Entity;
        }
    }

    void RemoveEntity(FEntity& Entity);

    template <typename T, typename... Args>
    void AddComponent(FEntity& ToEntity, Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );

        assert(ToEntity.GetUnderlyingIndex() != Swarm::Invalid);

        auto& EntityComponents =
            EntityToComponents[ToEntity.GetUnderlyingIndex()];

        if (EntityComponents.contains(T::GetType()))
        {
            return;
        }

        if (Components.contains(T::GetType()) == false)
        {
            Components[T::GetType()] = FComponentArray(T::GetType(), sizeof(T));
        }

        FComponentArray& ComponentArray = Components[T::GetType()];

        const Swarm::ComponentIndex NewIndex =
            ComponentArray.Add<T>(std::forward<Args>(Arguments)...);

        EntityComponents[T::GetType()] = NewIndex;
    }

    template <typename T>
    T& GetOrCreateComponent(FEntity& FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );

        assert(FromEntity.GetUnderlyingIndex() != Swarm::Invalid);

        auto& EntityComponents =
            EntityToComponents[FromEntity.GetUnderlyingIndex()];

        // Check if the entity has the component
        if (EntityComponents.contains(T::GetType()) == false)
        {
            AddComponent<T>(FromEntity);
        }

        const Swarm::ComponentIndex RequestIndex =
            EntityComponents[T::GetType()];

        return Components[T::GetType()].template GetItem<T>(RequestIndex);
    }

    template <typename T>
    void RemoveComponent(FEntity& FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );

        assert(FromEntity.GetUnderlyingIndex() != Swarm::Invalid);

        auto& EntityComponents =
            EntityToComponents[FromEntity.GetUnderlyingIndex()];

        // Check if the entity has the component
        if (EntityComponents.contains(T::GetType()) == false)
        {
            return;
        }

        const Swarm::ComponentIndex PendingRemoveIndex =
            EntityComponents[T::GetType()];

        // Remove component from the component array
        Components[T::GetType()].Remove(PendingRemoveIndex);

        // Update entity-to-components map
        EntityComponents.erase(T::GetType());
    }

private:
    std::map<
        Swarm::EntityIndex,
        std::map<Swarm::ComponentType, Swarm::ComponentIndex>>
        EntityToComponents;
    std::map<Swarm::ComponentType, FComponentArray> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;

private:
    Swarm::EntityIndex NextEntityIndex = 0;
    std::queue<Swarm::EntityIndex> FreeEntityIndices;
};

} // namespace Swarm
