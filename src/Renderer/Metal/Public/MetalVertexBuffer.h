#pragma once

#include "Vector.h"
#include "VertexBuffer.h"

namespace MTL
{
class Device;
class Buffer;
} // namespace MTL

struct FMetalVertexBuffer : public FVertexBuffer
{
    FMetalVertexBuffer(
        MTL::Device* Device, const std::vector<Math::FVector>& InVertex
    );

    MTL::Buffer* Data;
};
