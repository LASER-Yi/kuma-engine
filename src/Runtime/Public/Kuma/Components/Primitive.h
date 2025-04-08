#pragma once

#include "CoreMinimal.h"

#include "Swarm/Component.h"

#include <memory>

class FSceneProxy;
class FStaticMesh;

struct FPrimitiveComponent : public Swarm::FComponent
{
    FPrimitiveComponent(const std::shared_ptr<FStaticMesh> InMesh)
        : Swarm::FComponent(), Mesh(InMesh)
    {
    }

    const std::shared_ptr<FStaticMesh> Mesh;

    float YRotation = 0.0;
    float XRotation = 0.0;

    std::shared_ptr<FSceneProxy> SceneProxy;
};
