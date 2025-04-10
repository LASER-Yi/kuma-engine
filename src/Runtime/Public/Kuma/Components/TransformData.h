#pragma once

#include "CoreMinimal.h"
#include "MathFwd.h"

struct FTransformData : public Swarm::FComponent
{
    FTransform LocalTransform;

    /**
     * @brief The matrix from local space to the world space
     * Will be calculated by WorldHierarchicalSystem
     */
    FMatrix LocalToWorld = FMatrix::Identity;
};
