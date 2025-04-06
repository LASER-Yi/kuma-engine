#include "MetalVertexBuffer.h"
#include "Vector.h"

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <simd/simd.h>

FMetalVertexBuffer::FMetalVertexBuffer(
    MTL::Device* Device, const std::vector<Math::FVector>& InVertex
)
{
    static_assert(
        sizeof(Math::FVector) == sizeof(simd::float4),
        "The size of Math::FVector should be the same as simd::float4"
    );

    assert(Device);
    const size_t VertexDataSize = InVertex.size() * sizeof(Math::FVector);
    Data = Device->newBuffer(VertexDataSize, MTL::ResourceStorageModeManaged);

    std::memcpy(Data->contents(), InVertex.data(), VertexDataSize);
    Data->didModifyRange(NS::Range::Make(0, Data->length()));
}
