#pragma once

#include "Component.h"
#include "Definition.h"
#include "Manager.h"
#include "SystemUpdateContext.h"
#include "TypeHasher.h"

#include <functional>
#include <type_traits>
#include <unordered_map>

namespace Swarm
{

/**
 * @brief Defines the access mode for components in an entity query
 */
enum class EComponentAccessMode
{
    ReadOnly,   ///< Component can only be read
    ReadWrite,  ///< Component can be read and written
    Unspecific, ///< Component access mode is not specified
};

struct FEntityQueryResult;

/**
 * @brief Query system for filtering and iterating over entities with specific
 * components
 */
struct FEntityQuery
{
    FEntityQuery() = default;

    using Function = std::function<void(const FEntityQueryResult&)>;

    /**
     * @brief Iterates over all entities matching the query requirements
     * @param Context The system update context
     * @param Func Function to execute for each matching entity
     */
    void ForEach(const FSystemUpdateContext& Context, Function&& Func) const;

    /**
     * @brief Adds a component requirement to the query
     * @tparam T The component type to require
     * @param Mode The access mode for the component (default: ReadOnly)
     */
    template <typename T>
    void AddRequirement(
        EComponentAccessMode Mode = EComponentAccessMode::ReadOnly
    )
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();

        Requirements[TypeId] = Mode;
    }

    /**
     * @brief Gets the access mode requirement for a component type
     * @tparam T The component type to check
     * @return The access mode requirement for the component
     */
    template <typename T>
    EComponentAccessMode GetRequirement() const
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        const ClassHashType TypeId = FGenericTypeHasher::value<T>();

        if (Requirements.contains(TypeId))
        {
            return Requirements.at(TypeId);
        }

        return EComponentAccessMode::Unspecific;
    }

private:
    std::unordered_map<ClassHashType, EComponentAccessMode> Requirements;
};

/**
 * @brief Contains the result of an entity query, providing access to entity
 * components
 */
struct FEntityQueryResult
{
    friend class FEntityQuery;

    FEntityQueryResult(const FEntityQueryResult&) = delete;
    FEntityQueryResult& operator=(const FEntityQueryResult&) = delete;
    FEntityQueryResult(FEntityQueryResult&&) = delete;
    FEntityQueryResult& operator=(FEntityQueryResult&) = delete;

    /**
     * @brief Get component with read-only access
     * @tparam T The component type to retrieve
     * @return Const pointer to the component
     * @throws Fatal error if access mode is mismatched
     */
    template <typename T>
    const T* GetComponent() const
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        assert(
            Instigator->GetRequirement<T>() == EComponentAccessMode::ReadOnly
        );

        Manager* SwarmMgr = Context->Manager;

        const T* Component = SwarmMgr->GetComponent<T>(Entity);
        assert(Component);

        return Component;
    }

    /**
     * @brief Get component with read-write access
     * @tparam T The component type to retrieve
     * @return Pointer to the component
     * @throws Fatal error if access mode is mismatched
     */
    template <typename T>
    T* GetComponentReadWrite() const
    {
        static_assert(
            std::is_base_of<FComponent, T>::value,
            "T must be derived from FComponent"
        );

        assert(
            Instigator->GetRequirement<T>() == EComponentAccessMode::ReadWrite
        );

        Manager* SwarmMgr = Context->Manager;

        T* Component = SwarmMgr->GetComponent<T>(Entity);
        assert(Component);

        return Component;
    }

    /**
     * @brief Get the entity's signature
     * @return The entity signature
     */
    SignatureType GetEntity() const { return Entity; }

private:
    FEntityQueryResult(
        SignatureType InEntity, const FEntityQuery* InInstigator,
        const FSystemUpdateContext* InContext
    );

    SignatureType Entity;

    const FSystemUpdateContext* Context;
    const FEntityQuery* Instigator;
};

} // namespace Swarm
