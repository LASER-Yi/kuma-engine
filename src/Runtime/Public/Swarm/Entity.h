#pragma once

#include "CoreMinimal.h"
#include "Swarm/EntityBase.h"
#include "Swarm/Manager.h"

namespace Swarm
{

struct FEntity : public FEntityBase
{
    template <typename T, typename... Args>
    bool AddComponent(Args... Arguments)
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
};

} // namespace Swarm
