#pragma once

#include "MeshResource.h"

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
    MTL::Buffer* IndexBuffer;
};
