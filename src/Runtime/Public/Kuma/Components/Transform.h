#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"

struct FTransformComponent : public Swarm::FComponent
{
    FVector Position;
    FVector Rotation;
    FVector Scale;
};
