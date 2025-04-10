#include "MetalMesh.h"
#include "Metal/MTLResource.hpp"
#include "MetalDevice.h"

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
        sizeof(FVector) == sizeof(simd::float4),
        "The size of FVector should be the same as simd::float4"
    );

    MTL::Device* MetalDevice = Device->Get();
    assert(MetalDevice);

    assert(Descriptor.Vertices.size() == Descriptor.Normals.size());

    VertexCount = Descriptor.Indices.size();

    VertexBuffer = Create(
        MetalDevice, Descriptor.Vertices.data(),
        Descriptor.Vertices.size_bytes()
    );

    NormalBuffer = Create(
        MetalDevice, Descriptor.Normals.data(), Descriptor.Normals.size_bytes()
    );

    IndexBuffer = Create(
        MetalDevice, Descriptor.Indices.data(), Descriptor.Indices.size_bytes()
    );
}

FMetalMeshResource::~FMetalMeshResource()
{
    VertexBuffer->release();
    NormalBuffer->release();
    IndexBuffer->release();
}

MTL::Buffer* FMetalMeshResource::Create(
    MTL::Device* Device, const void* Data, size_t Size
)
{
    MTL::Buffer* Result =
        Device->newBuffer(Size, MTL::ResourceStorageModeManaged);

    std::memcpy(Result->contents(), Data, Size);
    Result->didModifyRange({0, Size});

    return Result;
}
