#pragma once

#include "CoreMinimal.h"

struct FMatrixComponent : public Swarm::FComponent
{
    Math::FTransform LocalTransform;
};
