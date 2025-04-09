#pragma once

#include "CoreMinimal.h"
#include "Swarm/EntityBase.h"
#include "Swarm/Manager.h"
#include <memory>
#include <utility>

namespace Swarm
{

/**
 * @brief Represent an entity in the swarm system.
 * @details This class is used to represent an entity in the swarm system. It
 * provide some helper function to manage the component
 */
struct FEntity : public FEntityBase
{
    FEntity(FEntityInitializationContext& Context);

    template <typename T, typename... Args>
    bool AddComponent(Args&&... Arguments)
    {
        return Swarm::Manager::Get()->AddComponent<T>(
            this, std::forward<Args>(Arguments)...
        );
    }

    template <typename T>
    T* GetComponent() const
    {
        return Swarm::Manager::Get()->GetComponent<T>(this);
    }

    template <typename T>
    void RemoveComponent()
    {
        Swarm::Manager::Get()->RemoveComponent<T>(this);
    }

    template <typename T>
    std::shared_ptr<T> GetShared()
    {
        std::shared_ptr<FEntityBase> base = shared_from_this();
        return std::static_pointer_cast<T>(base);
    }
};

} // namespace Swarm
