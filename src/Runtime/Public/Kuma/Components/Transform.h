#pragma once

#include "CoreMinimal.h"
#include "Transform.h"

struct FTransformComponent : public Swarm::FComponent
{
    Math::FTransform LocalTransform;
};
