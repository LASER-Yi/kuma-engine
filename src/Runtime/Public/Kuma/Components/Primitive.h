#pragma once

#include "CoreMinimal.h"

#include "Swarm/Component.h"
#include "Vector.h"
#include <memory>

class FSceneProxy;

struct FPrimitiveComponent : public Swarm::FComponent
{
    FPrimitiveComponent(const std::vector<FVector>& InVertex)
        : Swarm::FComponent(), Vertex(InVertex)
    {
    }

    std::vector<FVector> Vertex;

    std::shared_ptr<FSceneProxy> SceneProxy;
};
