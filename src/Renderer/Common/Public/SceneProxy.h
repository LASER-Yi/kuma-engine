#pragma once

#include "MathFwd.h"

#include <cstddef>
#include <memory>

class FStateObject;
class FRenderResource;
class FSceneRenderResource;
class FMeshRenderResource;

struct FSceneProxy
{
    std::size_t Signature;
    FMatrix ComponentToWorld;
    bool bStatic;
};

struct FPrimitiveSceneProxy : public FSceneProxy
{
    std::shared_ptr<FStateObject> PipelineStateObject;

    std::shared_ptr<FMeshRenderResource> MeshResource;
    std::shared_ptr<FRenderResource> InstanceResource;
    std::shared_ptr<FSceneRenderResource> SceneResource;
};

struct FCameraSceneProxy : public FSceneProxy
{
    FRadians FieldOfView;

    float NearClip;
    float FarClip;
};
