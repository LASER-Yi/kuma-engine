#pragma once

#include "Swarm/Interfaces/System.h"
#include "Swarm/Manager.h"

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

    KKumaEngine* GetEngine() const;
};

} // namespace Swarm
