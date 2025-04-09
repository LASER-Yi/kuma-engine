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

enum class EComponentAccessMode
{
    ReadOnly,
    ReadWrite,
    Unspecific,
};

struct FEntityQueryResult;

struct FEntityQuery
{
    FEntityQuery() = default;

    using Function = std::function<void(const FEntityQueryResult&)>;

    void ForEach(const FSystemUpdateContext& Context, Function&& Func) const;

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

struct FEntityQueryResult
{
    friend class FEntityQuery;

    FEntityQueryResult(const FEntityQueryResult&) = delete;
    FEntityQueryResult& operator=(const FEntityQueryResult&) = delete;
    FEntityQueryResult(FEntityQueryResult&&) = delete;
    FEntityQueryResult& operator=(FEntityQueryResult&) = delete;

    /**
     * @brief Get component with EComponentAccessMode == ReadOnly. An fatal
     * error will be throw if the access mode is mismatched
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
     * @brief Get component with EComponentAccessMode == ReadWrite. An fatal
     * error will be throw if the access mode is mismatched
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
     * Get the entity's signature
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
