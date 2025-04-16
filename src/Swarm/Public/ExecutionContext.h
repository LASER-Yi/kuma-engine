#pragma once

namespace Swarm
{

class Manager;

struct FExecutionContext
{
    float DeltaTime;
    Manager* Manager;
};

} // namespace Swarm
