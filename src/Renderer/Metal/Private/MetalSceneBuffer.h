#pragma once

#include "Matrix.h"
#include "RenderResource.h"

#include <memory>

namespace MTL
{
class Buffer;
} // namespace MTL

class KMetalDevice;

struct FMetalSceneBuffer : public FRenderResource
{
    FMetalSceneBuffer(
        std::shared_ptr<KMetalDevice> Device, const float AspectRatio,
        const Math::FMatrix& ComponentToWorld
    );

    MTL::Buffer* Data;
};
