#pragma once

#include "Matrix.h"
#include "TransformBuffer.h"

namespace MTL
{
class Buffer;
} // namespace MTL

class KMetalDevice;

struct FMetalTransBuffer : public FTransformBuffer
{
    FMetalTransBuffer(
        std::shared_ptr<KMetalDevice> Device, const float AspectRatio,
        const Math::FMatrix& ComponentToWorld
    );

    MTL::Buffer* Data;
};
