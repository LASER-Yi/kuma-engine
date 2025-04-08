#pragma once

#include "Matrix.h"
#include "RenderResource.h"
#include "Rotator.h"

struct FRendererCameraDescriptor
{
    float AspectRatio;
    Math::FRadians FieldOfView;
    Math::FMatrix WorldToCamera;
};

struct FRendererPrimitiveDescriptor
{
    Math::FMatrix ModelToWorld;
};

struct FSceneRenderResource : public FRenderResource
{
    virtual void Update(
        const FRendererCameraDescriptor& Camera,
        const FRendererPrimitiveDescriptor& Primitive
    ) = 0;
};
