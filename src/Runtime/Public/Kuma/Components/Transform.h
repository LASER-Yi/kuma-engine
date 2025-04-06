#pragma once

#include "CoreMinimal.h"
#include "Transform.h"

struct FMatrixComponent : public Swarm::FComponent
{
    Math::FMatrix LocalTransform;
};
