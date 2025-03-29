#pragma once

#include "Core/CoreMinimal.h"

namespace Swarm
{

class ISystem
{
  public:
    virtual void Initialize() = 0;

    virtual void Tick(float DeltaTime) = 0;

    virtual void Shutdown() = 0;

  protected:
    // TODO: Figure out how to implement this
    void QueryEntity() const;
};

} // namespace Swarm
