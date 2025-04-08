#include "MetalMesh.h"
#include "Metal/MTLResource.hpp"
#include "MetalDevice.h"
#include "Vector.h"

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <cassert>
#include <memory>
#include <simd/simd.h>

FMetalMeshResource::FMetalMeshResource(
    std::shared_ptr<KMetalDevice> Device,
    const FMeshResourceDescriptor& Descriptor
)
{
    static_assert(
        sizeof(Math::FVector) == sizeof(simd::float4),
        "The size of Math::FVector should be the same as simd::float4"
    );

    MTL::Device* MetalDevice = Device->Get();
    assert(MetalDevice);

    VertexCount = Descriptor.Indices.size();

    // Vertex buffer
    {
        const size_t VertexDataSize = Descriptor.Vertices.size_bytes();
        VertexBuffer = MetalDevice->newBuffer(
            VertexDataSize, MTL::ResourceStorageModeManaged
        );

        std::memcpy(
            VertexBuffer->contents(), Descriptor.Vertices.data(), VertexDataSize
        );
        VertexBuffer->didModifyRange({0, VertexDataSize});
    }

    // Index buffer
    {
        const size_t IndexDataSize = Descriptor.Indices.size_bytes();
        IndexBuffer = MetalDevice->newBuffer(
            IndexDataSize, MTL::ResourceStorageModeManaged
        );

        std::memcpy(
            IndexBuffer->contents(), Descriptor.Indices.data(), IndexDataSize
        );
        IndexBuffer->didModifyRange({0, IndexDataSize});
    }
}

FMetalMeshResource::~FMetalMeshResource()
{
    VertexBuffer->release();
    IndexBuffer->release();
}
