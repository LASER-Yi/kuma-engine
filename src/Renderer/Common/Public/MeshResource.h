#pragma once

#include "MathFwd.h"
#include "RenderResource.h"

#include <span>

struct FMeshResourceDescriptor
{
    std::span<const FVector> Vertices;
    std::span<const FVector> Normals;
    std::span<const std::uint16_t> Indices;
};

struct FMeshRenderResource : public FRenderResource
{
};
