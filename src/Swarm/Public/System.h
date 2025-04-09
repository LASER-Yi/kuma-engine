#pragma once

#include "Interfaces/System.h"
#include "Manager.h"

class KKumaEngine;

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
