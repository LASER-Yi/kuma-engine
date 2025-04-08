#pragma once

#include "RenderResource.h"
#include "Vector.h"

#include <span>

struct FMeshResourceDescriptor
{
    std::span<const Math::FVector> Vertices;
    std::span<const std::uint16_t> Indices;
};

struct FMeshRenderResource : public FRenderResource
{
};
