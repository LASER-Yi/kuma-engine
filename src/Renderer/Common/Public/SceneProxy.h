#pragma once

#include "Matrix.h"

#include <memory>

class FStateObject;
class FRenderResource;
class FSceneRenderResource;
class FMeshRenderResource;

struct FSceneProxy
{
    Math::FMatrix ComponentToWorld;

    std::shared_ptr<FStateObject> PipelineStateObject;
    std::shared_ptr<FSceneRenderResource> SceneBuffer;

    // The following members belongs to the primitive, we will need to
    // move them to elsewhere in the future
    std::shared_ptr<FMeshRenderResource> MeshResource;
};
