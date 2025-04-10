#pragma once

#include "CoreMinimal.h"
#include "Matrix.h"

struct FTransformData : public Swarm::FComponent
{
    Math::FTransform LocalTransform;

    /**
     * @brief The matrix from local space to the world space
     * Will be calculated by WorldHierarchicalSystem
     */
    Math::FMatrix LocalToWorld = Math::FMatrix::Identity;
};
