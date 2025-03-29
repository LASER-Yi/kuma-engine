#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"

struct FTransformComponent : public Swarm::IComponent<FTransformComponent>
{
    FVector Position;
    FVector Rotation;
    FVector Scale;
};
