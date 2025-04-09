#pragma once

#include "CoreMinimal.h"

struct FTransformComponent : public Swarm::FComponent
{
    Math::FTransform LocalTransform;
};
