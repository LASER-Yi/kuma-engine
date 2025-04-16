#pragma once

#include "Component.h"
#include "Containers/HandleAllocator.h"
#include "Containers/TypedArray.h"
#include "Definition.h"
#include "EntityBase.h"
#include "System.h"
#include "Templates/Singleton.h"

#include <cassert>
#include <map>
#include <memory>
#include <span>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Swarm
{

struct FEntityInitializationContext
{
    FEntityInitializationContext() = default;
    FEntityInitializationContext(const FEntityInitializationContext&) = delete;
    FEntityInitializationContext&
    operator=(const FEntityInitializationContext&) = delete;

    std::unordered_map<Swarm::ClassHashType, Swarm::SignatureType>
        DefaultComponents;

    template <typename T, typename... Args>
    void CreateDefaultComponent(Args&&... Arguments);
};

class Manager final : public TSingleton<Swarm::Manager>
{
public:
    Manager() = default;

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Shutdown();

    void Update(float DeltaTime);

    /**
     * @brief Creates a new entity of type T
     * @tparam T Entity type that must derive from FEntityBase
     * @return Newly created entity of type T
     * @throws static_assert if T is not derived from FEntityBase or has
     * different size (you cannot add new members to T)
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> MakeEntity(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<FEntityBase, T>::value,
            "T must be derived from FEntityBase"
        );

        static_assert(
            sizeof(T) == sizeof(FEntityBase),
            "T must be the same size as FEntityBase"
        );

        const Swarm::SignatureType EntitySign = EntitySignature.Allocate();

        FEntityInitializationContext Context;

        auto NewEntity =
            std::make_shared<T>(Context, std::forward<Args>(Arguments)...);
        NewEntity->Signature = EntitySign;

        // Now let's add those default components
        auto& EntityComponents = EntityToComponents[EntitySign];
        EntityComponents.merge(Context.DefaultComponents);

        return NewEntity;
    }

    /**
     * Removes the specified entity from the swarm.
     *
     * @param Entity An entity to be removed.
     */
    void RemoveEntity(FEntityBase* Entity);

    /**
     * @brief Get the entity via component types
     */
    void FilterEntityByComponents(
        std::vector<SignatureType>& OutEntities,
        const std::span<SignatureType>& InComponents
    );

    template <typename T, typename... Args>
    std::tuple<Swarm::ClassHashType, Swarm::SignatureType> CreateComponent(
        Args&&... Arguments
    )
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        const Swarm::ClassHashType ComponentType =
            FGenericTypeHasher::value<T>();
        const Swarm::SignatureType ComponentSignature =
            Components.Add<T>(std::forward<Args>(Arguments)...);

        return {ComponentType, ComponentSignature};
    }

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
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        if (ToEntity == nullptr)
        {
            return false;
        }

        assert(ToEntity->Signature != Swarm::InvalidSignature);

        auto& EntityComponents = EntityToComponents[ToEntity->Signature];

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();

        // Prevent adding duplicate components to the same entity
        // as each entity should have at most one instance of a specific
        // component type.
        if (EntityComponents.contains(TypeId))
        {
            return false;
        }

        const auto [CompType, CompSign] =
            CreateComponent<T>(std::forward<Args>(Arguments)...);

        assert(TypeId == CompType);

        EntityComponents[CompType] = CompSign;

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
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        if (FromEntity == nullptr)
        {
            return nullptr;
        }

        assert(FromEntity->Signature != Swarm::InvalidSignature);

        return GetComponent<T>(FromEntity->Signature);
    }

    /**
     * @brief Get a component of type T from the specified entity.
     * @tparam T The type of the component to be retrieved.
     * @param EntitySignature The entity which the component will be retrieved.
     * @return A pointer to the component of type T, or nullptr if the component
     * does not exist.
     */
    template <typename T>
    T* GetComponent(SignatureType EntitySignature)
    {
        assert(EntitySignature != Swarm::InvalidSignature);

        if (EntityToComponents.contains(EntitySignature) == false)
        {
            return nullptr;
        }

        auto& EntityComponents = EntityToComponents.at(EntitySignature);

        // Check if the entity has the component
        const ClassHashType TypeId = FGenericTypeHasher::value<T>();
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
    template <typename T>
    void RemoveComponent(FEntityBase* FromEntity)
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        if (FromEntity == nullptr)
        {
            return;
        }

        assert(FromEntity->Signature != Swarm::InvalidSignature);

        auto& EntityComponents = EntityToComponents[FromEntity->Signature];
        const ClassHashType TypeId = FGenericTypeHasher::value<T>();

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
     * @brief Retrieves a span of components of the specified type.
     *
     * This method returns a view (std::span) of all components of type T
     * that are managed by the system. The type T must be derived from the
     * FComponent base class.
     *
     * @tparam T The type of components to retrieve. Must inherit from
     * FComponent.
     * @return std::span<T> A span containing all components of type T.
     */
    template <typename T>
    std::span<T> GetComponents() const
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        return Components.GetView<T>();
    }

    /**
     * @brief Get the number of components of type T in the swarm.
     * @tparam T The type of the component to be counted.
     * @return The number of components of type T in the swarm.
     */
    template <typename T>
    std::size_t GetComponentCount()
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        return Components.Count<T>();
    }

    template <typename T, typename... Args>
    void AddSystem(Args&&... Arguments)
    {
        static_assert(
            std::is_base_of<KSystem, T>::value, "T must be derived from KSystem"
        );

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();
        if (Systems.contains(TypeId))
        {
            return;
        }

        auto NewSystem = std::make_shared<T>(std::forward<Args>(Arguments)...);
        NewSystem->Initialize();

        Systems[TypeId] = NewSystem;
    }

    template <typename T>
    void RemoveSystem()
    {
        static_assert(
            std::is_base_of<KSystem, T>::value, "T must be derived from KSystem"
        );

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();
        if (Systems.contains(TypeId) == false)
        {
            return;
        }

        Systems[TypeId]->Shutdown();

        Systems.erase(TypeId);
    }

    template <typename T>
    std::weak_ptr<T> GetSystem()
    {
        static_assert(
            std::is_base_of<KSystem, T>::value, "T must be derived from KSystem"
        );

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();
        if (Systems.contains(TypeId) == false)
        {
            return nullptr;
        }

        return Systems.at(TypeId);
    }

private:
    std::map<
        Swarm::SignatureType,
        std::unordered_map<Swarm::ClassHashType, Swarm::SignatureType>>
        EntityToComponents;

    TTypedArray<FComponent, Swarm::SignatureType, Swarm::ClassHashType>
        Components;
    std::unordered_map<Swarm::ClassHashType, std::shared_ptr<KSystem>> Systems;

public:
    THandleAllocator<Swarm::SignatureType> EntitySignature;
};

template <typename T, typename... Args>
void FEntityInitializationContext::CreateDefaultComponent(Args&&... Arguments)
{
    const auto [ComponentType, ComponentSign] =
        Swarm::Manager::Get()->CreateComponent<T>(std::forward<Args>(Arguments
        )...);

    assert(DefaultComponents.contains(ComponentType) == false);

    DefaultComponents[ComponentType] = ComponentSign;
}

} // namespace Swarm
