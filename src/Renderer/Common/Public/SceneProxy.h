#pragma once

#include "Matrix.h"

#include <memory>

class FStateObject;
class FRenderResource;

struct FSceneProxy
{
    Math::FMatrix ComponentToWorld;

    std::shared_ptr<FStateObject> PipelineStateObject;
    std::shared_ptr<FRenderResource> SceneBuffer;

    // The following members belongs to the primitive, we will need to
    // move them to elsewhere in the future
    std::shared_ptr<FRenderResource> VertexBuffer;
    std::shared_ptr<FRenderResource> ColorBuffer;
    size_t VertexCount;
};
