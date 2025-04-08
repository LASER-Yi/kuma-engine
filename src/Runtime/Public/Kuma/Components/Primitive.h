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

    std::shared_ptr<FSceneProxy> SceneProxy;
};
