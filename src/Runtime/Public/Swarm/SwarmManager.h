#pragma once

#include "Core/Templates/Singleton.h"
#include "CoreMinimal.h"
#include "Swarm/Definition.h"
#include "Swarm/Entity.h"
#include "Swarm/Interfaces/Component.h"
#include "Swarm/Interfaces/System.h"
#include "Swarm/Utilities/ComponentArray.h"

#include <cassert>
#include <map>
#include <memory>
#include <queue>
#include <vector>

namespace Swarm
{

class KManager final : public TSingleton<Swarm::KManager>
{
public:
    KManager();
    ~KManager();

    KManager(const KManager&) = delete;
    KManager& operator=(const KManager&) = delete;

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
    bool AddComponent(FEntity& ToEntity, Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        if (ToEntity.GetUnderlyingIndex() == Swarm::InvalidIndex)
        {
            return false;
        }

        auto& EntityComponents =
            EntityToComponents[ToEntity.GetUnderlyingIndex()];

        // Prevent adding duplicate components to the same entity
        // as each entity should have at most one instance of a specific
        // component type.
        if (EntityComponents.contains(T::GetType()))
        {
            return false;
        }

        if (Components.contains(T::GetType()) == false)
        {
            Components[T::GetType()] = FComponentArray(T::GetType(), sizeof(T));
        }

        FComponentArray& ComponentArray = Components[T::GetType()];

        const Swarm::ComponentIndex NewIndex =
            ComponentArray.Add<T>(std::forward<Args>(Arguments)...);

        EntityComponents[T::GetType()] = NewIndex;

        return true;
    }

    template <typename T>
    T* GetComponent(FEntity& FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        assert(FromEntity.GetUnderlyingIndex() != Swarm::InvalidIndex);

        auto& EntityComponents =
            EntityToComponents[FromEntity.GetUnderlyingIndex()];

        // Check if the entity has the component
        if (EntityComponents.contains(T::GetType()) == false)
        {
            return nullptr;
        }

        const Swarm::ComponentIndex RequestIndex =
            EntityComponents[T::GetType()];

        return Components[T::GetType()].template GetItem<T>(RequestIndex);
    }

    template <typename T>
    void RemoveComponent(FEntity& FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        assert(FromEntity.GetUnderlyingIndex() != Swarm::InvalidIndex);

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

    template <typename T>
    std::size_t GetComponentCount()
    {
        if (Components.contains(T::GetType()) == false)
        {
            return 0;
        }

        return Components[T::GetType()].GetSize();
    }

private:
    std::map<
        Swarm::EntityIndex,
        std::map<Swarm::ComponentType, Swarm::ComponentIndex>>
        EntityToComponents;
    std::unordered_map<Swarm::ComponentType, FComponentArray> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;

private:
    Swarm::EntityIndex NextEntityIndex = 0;
    std::queue<Swarm::EntityIndex> FreeEntityIndices;
};

} // namespace Swarm
