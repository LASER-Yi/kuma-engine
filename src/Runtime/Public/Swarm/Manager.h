#pragma once

#include "CoreMinimal.h"

#include "Core/Templates/Singleton.h"
#include "Swarm/Component.h"
#include "Swarm/Containers/Signature.h"
#include "Swarm/Containers/TypedArray.h"
#include "Swarm/Definition.h"
#include "Swarm/EntityBase.h"
#include "Swarm/Interfaces/System.h"

#include <cassert>
#include <map>
#include <memory>
#include <unordered_map>
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
    template <
        typename T, typename... Args,
        std::enable_if_t<std::is_base_of<FEntityBase, T>::value, bool> = true>
    std::shared_ptr<T> MakeEntity(Args&&... Arguments)
    {
        static_assert(
            sizeof(T) == sizeof(FEntityBase),
            "T must be the same size as FEntityBase"
        );

        const Swarm::SignatureType NewSignature = EntitySignature.Allocate();

        return std::make_shared<T>(
            NewSignature, std::forward<Args>(Arguments)...
        );
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
    template <
        typename T, typename... Args,
        std::enable_if_t<std::is_base_of<FComponent, T>::value, bool> = true>
    bool AddComponent(FEntityBase* ToEntity, Args&&... Arguments)
    {
        if (ToEntity == nullptr)
        {
            return false;
        }

        if (ToEntity->GetSignature() == Swarm::InvalidSignature)
        {
            return false;
        }

        auto& EntityComponents = EntityToComponents[ToEntity->GetSignature()];

        const size_t TypeId = typeid(T).hash_code();

        // Prevent adding duplicate components to the same entity
        // as each entity should have at most one instance of a specific
        // component type.
        if (EntityComponents.contains(TypeId))
        {
            return false;
        }

        const Swarm::SignatureType NewComponent =
            Components.Add<T>(std::forward<Args>(Arguments)...);

        EntityComponents[TypeId] = NewComponent;

        return true;
    }

    /**
     * @brief Get a component of type T from the specified entity.
     * @tparam T The type of the component to be retrieved.
     * @param FromEntity The entity from which the component will be retrieved.
     * @return A pointer to the component of type T, or nullptr if the component
     * does not exist.
     */
    template <
        typename T,
        std::enable_if_t<std::is_base_of<FComponent, T>::value, bool> = true>
    T* GetComponent(const FEntityBase* FromEntity)
    {
        if (FromEntity == nullptr)
        {
            return nullptr;
        }

        assert(FromEntity->GetSignature() != Swarm::InvalidSignature);

        auto& EntityComponents =
            EntityToComponents.at(FromEntity->GetSignature());

        // Check if the entity has the component
        const size_t TypeId = typeid(T).hash_code();
        if (EntityComponents.contains(TypeId) == false)
        {
            return nullptr;
        }

        const Swarm::SignatureType RequestSignature =
            EntityComponents.at(TypeId);

        return Components.Find<T>(RequestSignature);
    }

    /**
     * @brief Remove a component of type T from the specified entity.
     * @tparam T The type of the component to be removed.
     * @param FromEntity The entity from which the component will be removed.
     */
    template <
        typename T,
        std::enable_if_t<std::is_base_of<FComponent, T>::value, bool> = true>
    void RemoveComponent(FEntityBase* FromEntity)
    {

        if (FromEntity == nullptr)
        {
            return;
        }

        assert(FromEntity->GetSignature() != Swarm::InvalidSignature);

        auto& EntityComponents = EntityToComponents[FromEntity->GetSignature()];
        const size_t TypeId = typeid(T).hash_code();

        // Check if the entity has the component
        if (EntityComponents.contains(TypeId) == false)
        {
            return;
        }

        const Swarm::SignatureType RemoveSignature = EntityComponents[TypeId];

        // Remove component from the component array
        Components.Remove<T>(RemoveSignature);

        // Update entity-to-components map
        EntityComponents.erase(TypeId);
    }

    /**
     * @brief Get the number of components of type T in the swarm.
     * @tparam T The type of the component to be counted.
     * @return The number of components of type T in the swarm.
     */
    template <
        typename T,
        std::enable_if_t<std::is_base_of<FComponent, T>::value, bool> = true>
    std::size_t GetComponentCount()
    {
        return Components.Count<T>();
    }

private:
    std::map<
        Swarm::SignatureType,
        std::unordered_map<std::size_t, Swarm::SignatureType>>
        EntityToComponents;

    TTypedArray<Swarm::SignatureType> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;

public:
    TSignature<Swarm::SignatureType> EntitySignature;
};

} // namespace Swarm
