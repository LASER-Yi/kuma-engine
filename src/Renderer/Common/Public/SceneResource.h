#pragma once

#include "MathFwd.h"
#include "RenderResource.h"

struct FRendererCameraDescriptor
{
    float AspectRatio;
    FRadians FieldOfView;
    FMatrix WorldToCamera;

    float Near;
    float Far;
};

struct FRendererPrimitiveDescriptor
{
    FMatrix ModelToWorld;
};

struct FSceneRenderResource : public FRenderResource
{
    virtual void Update(const FRendererCameraDescriptor& Camera) = 0;
};
