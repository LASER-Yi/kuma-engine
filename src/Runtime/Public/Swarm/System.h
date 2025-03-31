#pragma once

#include "Swarm/Interfaces/System.h"
#include "Swarm/Manager.h"

namespace Swarm
{

class KSystem : public Swarm::ISystem
{
protected:
    template <typename T>
    std::span<T> GetComponents() const
    {
        return Swarm::Manager::Get()->GetComponents<T>();
    }
};

} // namespace Swarm
