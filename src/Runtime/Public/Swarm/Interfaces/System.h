#pragma once

#include "CoreMinimal.h"

namespace Swarm
{

/**
 * @brief Interface for all systems in the swarm.
 * @details This interface defines the basic structure for all systems in the
 * swarm. Each system must implement the Initialize, Update, and Shutdown
 * methods.
 */
class ISystem
{
public:
    virtual void Initialize() = 0;

    virtual void Execute(float DeltaTime) = 0;

    virtual void Shutdown() = 0;

public:
    ISystem() = default;
    virtual ~ISystem() {}

    ISystem(const ISystem&) = delete;
    ISystem& operator=(const ISystem&) = delete;
    ISystem(ISystem&&) = delete;
    ISystem& operator=(ISystem&&) = delete;
};

} // namespace Swarm
