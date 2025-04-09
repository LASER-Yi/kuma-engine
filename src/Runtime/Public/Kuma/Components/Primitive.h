#pragma once

#include "CoreMinimal.h"

#include "Component.h"

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

    std::shared_ptr<FSceneProxy> SceneProxy;
};
