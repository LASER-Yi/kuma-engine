#include "Core/CoreMinimal.h"

class ISwarmSystem
{
public:
    virtual void Initialize() = 0;

    virtual void Tick(float DeltaTime) = 0;

    virtual void Shutdown() = 0;
};
