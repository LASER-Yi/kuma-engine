#pragma once

#include "CoreMinimal.h"
#include "Swarm/Definition.h"
#include <typeinfo>

namespace Swarm
{

template <typename T>
class IComponent
{
public:
    static constexpr Swarm::ComponentType GetType()
    {
        return typeid(T).hash_code();
    }
};

} // namespace Swarm
