#pragma once

namespace Swarm
{

class Manager;

struct FSystemUpdateContext
{
    float DeltaTime;
    Manager* Manager;
};

} // namespace Swarm
