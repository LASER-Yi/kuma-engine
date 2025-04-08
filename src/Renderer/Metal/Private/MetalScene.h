#pragma once

#include "SceneResource.h"

#include <memory>

namespace MTL
{
class Buffer;
} // namespace MTL

class KMetalDevice;

struct FMetalSceneResource : public FSceneRenderResource
{
    FMetalSceneResource(std::shared_ptr<KMetalDevice> Device);
    ~FMetalSceneResource();

    virtual void Update(
        const FRendererCameraDescriptor& Camera,
        const FRendererPrimitiveDescriptor& Primitive
    ) override;

    MTL::Buffer* Data;
};
