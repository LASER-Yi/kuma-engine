#pragma once

#include "MeshResource.h"
#include "Metal/MTLDevice.hpp"

#include <memory>

namespace MTL
{
class Buffer;
} // namespace MTL

class KMetalDevice;

struct FMetalMeshResource : public FMeshRenderResource
{
    FMetalMeshResource(
        std::shared_ptr<KMetalDevice> Device,
        const FMeshResourceDescriptor& InDescriptor
    );

    ~FMetalMeshResource();

    size_t VertexCount;
    MTL::Buffer* VertexBuffer;
    MTL::Buffer* NormalBuffer;
    MTL::Buffer* IndexBuffer;

private:
    MTL::Buffer* Create(MTL::Device* Device, const void* Data, size_t Size);
};
