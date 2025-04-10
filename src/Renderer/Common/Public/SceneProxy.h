#pragma once

#include "Matrix.h"
#include "Rotator.h"

#include <cstddef>
#include <memory>

class FStateObject;
class FRenderResource;
class FSceneRenderResource;
class FMeshRenderResource;

struct FSceneProxy
{
    Math::FMatrix ComponentToWorld;

    std::size_t Signature;
};

struct FPrimitiveSceneProxy : public FSceneProxy
{
    std::shared_ptr<FStateObject> PipelineStateObject;
    std::shared_ptr<FSceneRenderResource> SceneBuffer;

    // The following members belongs to the primitive, we will need to
    // move them to elsewhere in the future
    std::shared_ptr<FMeshRenderResource> MeshResource;
};

struct FCameraSceneProxy : public FSceneProxy
{
    Math::FRadians FieldOfView;

    float NearClip;
    float FarClip;
};
