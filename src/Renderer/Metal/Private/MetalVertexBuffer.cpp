#include "MetalVertexBuffer.h"
#include "Vector.h"

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLDevice.hpp>

FMetalVertexBuffer::FMetalVertexBuffer(
    MTL::Device* Device, const std::vector<FVector>& InVertex
)
{
    assert(Device);
    const size_t VertexDataSize = InVertex.size() * sizeof(FVector);
    Data = Device->newBuffer(VertexDataSize, MTL::ResourceStorageModeManaged);

    std::memcpy(Data->contents(), InVertex.data(), VertexDataSize);
    Data->didModifyRange(NS::Range::Make(0, Data->length()));
}
