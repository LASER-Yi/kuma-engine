#pragma once

#include "Component.h"
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
};

struct FEntityQueryResult
{
    /**
     * @brief Get component with EComponentAccessMode == ReadOnly. An fatal
     * error will be throw if the access mode is mismatched
     */
    template <typename T>
    const T* GetComponent() const
    {
        return nullptr;
    }

    /**
     * @brief Get component with EComponentAccessMode == ReadWrite. An fatal
     * error will be throw if the access mode is mismatched
     */
    template <typename T>
    T* GetComponentReadWrite() const
    {
        return nullptr;
    }
};

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

private:
    std::unordered_map<ClassHashType, EComponentAccessMode> Requirements;
};

} // namespace Swarm
