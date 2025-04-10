#pragma once

#include "CoreMinimal.h"
#include "MathFwd.h"

enum class EMovementMode : std::uint8_t
{
    Static,
    Dynamic,
};

struct FTransformData : public Swarm::FComponent
{
    FTransform LocalTransform;

    EMovementMode MovementMode = EMovementMode::Static;

    /**
     * @brief The matrix from local space to the world space
     * Will be calculated by WorldHierarchicalSystem
     */
    FMatrix LocalToWorld;
};
