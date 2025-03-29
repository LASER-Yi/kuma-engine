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

    virtual void Update(float DeltaTime) = 0;

    virtual void Shutdown() = 0;

protected:
    // TODO: Figure out how to implement this
    void QueryEntity() const;
};

} // namespace Swarm
