#pragma once

#include "RenderResource.h"
#include "Vector.h"

#include <vector>

namespace MTL
{
class Device;
class Buffer;
} // namespace MTL

struct FMetalVertexBuffer : public FRenderResource
{
    FMetalVertexBuffer(
        MTL::Device* Device, const std::vector<Math::FVector>& InVertex
    );

    ~FMetalVertexBuffer();

    MTL::Buffer* Data;
};
