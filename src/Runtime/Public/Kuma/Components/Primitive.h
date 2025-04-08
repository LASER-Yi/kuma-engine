#pragma once

#include "CoreMinimal.h"

#include "Swarm/Component.h"
#include "Vector.h"

#include <memory>

class FSceneProxy;

struct FPrimitiveComponent : public Swarm::FComponent
{
    FPrimitiveComponent(
        const std::vector<Math::FVector>& InVertex,
        const std::vector<Math::FVector>& InColor
    )
        : Swarm::FComponent(), Vertex(InVertex), Color(InColor)
    {
    }

    std::vector<Math::FVector> Vertex;
    std::vector<Math::FVector> Color;

    float YRotation = 0.0;
    float XRotation = 0.0;

    std::shared_ptr<FSceneProxy> SceneProxy;
};
