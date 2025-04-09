#pragma once

#include "EntityQuery.h"

#include "Interfaces/System.h"

class KKumaEngine;

namespace Swarm
{

class KSystem : public Swarm::ISystem
{
public:
    FEntityQuery Query;
};

} // namespace Swarm
