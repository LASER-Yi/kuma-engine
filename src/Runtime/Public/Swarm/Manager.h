#pragma once

#include "Core/Templates/Singleton.h"
#include "CoreMinimal.h"
#include "Swarm/EntityBase.h"
#include "Swarm/Interfaces/System.h"
#include "Swarm/Utilities/ComponentArray.h"

#include <cassert>
#include <map>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

namespace Swarm
{

class Manager final : public TSingleton<Swarm::Manager>
{
public:
    Manager();
    ~Manager();

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Update(float DeltaTime);

    /**
     * @brief Creates a new entity of type T
     * @tparam T Entity type that must derive from FEntityBase
     * @return Newly created entity of type T
     * @throws static_assert if T is not derived from FEntityBase or has
     * different size (you cannot add new members to T)
     */
    template <typename T, typename... Args>
    T MakeEntity(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<FEntityBase, T>::value,
            "T must be derived from FEntityBase"
        );

        static_assert(
            sizeof(T) == sizeof(FEntityBase),
            "T must be the same size as FEntityBase"
        );

        T Entity(std::forward<Args>(Arguments)...);
        if (FreeEntityIndices.empty() == false)
        {
            const Swarm::EntityIndex NextIndex = FreeEntityIndices.front();
            FreeEntityIndices.pop();

            Entity.InternalSetUnderlyingIndex(NextIndex);
        }
        else
        {
            Entity.InternalSetUnderlyingIndex(NextEntityIndex);
            ++NextEntityIndex;

            assert(
                NextEntityIndex < std::numeric_limits<Swarm::EntityIndex>::max()
            );
        }

        return Entity;
    }

    /**
     * Removes the specified entity from the swarm.
     *
     * @param Entity An entity to be removed.
     */
    void RemoveEntity(FEntityBase* Entity);

    /**
     * @brief Add a new component to the specified entity.
     * @tparam T The type of the component to be added.
     * @param ToEntity The entity to which the component will be added.
     * @param Arguments The arguments to be passed to the component constructor.
     * @return true if the component was added successfully, false otherwise.
     */
    template <typename T, typename... Args>
    bool AddComponent(FEntityBase* ToEntity, Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        if (ToEntity == nullptr)
        {
            return false;
        }

        if (ToEntity->GetUnderlyingIndex() == Swarm::InvalidIndex)
        {
            return false;
        }

        auto& EntityComponents =
            EntityToComponents[ToEntity->GetUnderlyingIndex()];

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

    /**
     * @brief Get a component of type T from the specified entity.
     * @tparam T The type of the component to be retrieved.
     * @param FromEntity The entity from which the component will be retrieved.
     * @return A pointer to the component of type T, or nullptr if the component
     * does not exist.
     */
    template <typename T>
    T* GetComponent(const FEntityBase* FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        if (FromEntity == nullptr)
        {
            return nullptr;
        }

        assert(FromEntity->GetUnderlyingIndex() != Swarm::InvalidIndex);

        auto& EntityComponents =
            EntityToComponents[FromEntity->GetUnderlyingIndex()];

        // Check if the entity has the component
        if (EntityComponents.contains(T::GetType()) == false)
        {
            return nullptr;
        }

        const Swarm::ComponentIndex RequestIndex =
            EntityComponents[T::GetType()];

        return Components[T::GetType()].template GetItem<T>(RequestIndex);
    }

    /**
     * @brief Remove a component of type T from the specified entity.
     * @tparam T The type of the component to be removed.
     * @param FromEntity The entity from which the component will be removed.
     */
    template <typename T>
    void RemoveComponent(FEntityBase* FromEntity)
    {
        static_assert(
            std::is_base_of<IComponent<T>, T>::value,
            "T must be derived from IComponent"
        );

        if (FromEntity == nullptr)
        {
            return;
        }

        assert(FromEntity->GetUnderlyingIndex() != Swarm::InvalidIndex);

        auto& EntityComponents =
            EntityToComponents[FromEntity->GetUnderlyingIndex()];

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

    /**
     * @brief Get the number of components of type T in the swarm.
     * @tparam T The type of the component to be counted.
     * @return The number of components of type T in the swarm.
     */
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
