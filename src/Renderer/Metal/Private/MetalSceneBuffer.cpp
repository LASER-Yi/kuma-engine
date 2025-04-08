#include "MetalSceneBuffer.h"
#include "Matrix.h"
#include "MetalDevice.h"
#include "Rotator.h"

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <Metal/MTLResource.hpp>
#include <simd/simd.h>

FMetalSceneBuffer::FMetalSceneBuffer(
    std::shared_ptr<KMetalDevice> Device, const float AspectRatio,
    const Math::FMatrix& ComponentToWorld
)
{
    static_assert(
        sizeof(Math::FMatrix) == sizeof(simd::float4x4),
        "The size of Math::FMatrix should be the same as simd::float4x4"
    );

    MTL::Device* MetalDevice = Device->Get();

    const auto FieldOfView = Math::FRadians::From(Math::FDegrees(45.0));

    struct FShaderBuffer
    {
        Math::FMatrix Perspective;
        Math::FMatrix WorldToCamera;
        Math::FMatrix ModelToWorld;
    };

    FShaderBuffer BufferData = {
        .Perspective = Math::FMatrix::MakePerspective(
            FieldOfView, AspectRatio, 0.1, 100.0
        ),
        .WorldToCamera = Math::FMatrix::MakePosition({0.0, 0.0, -5.0}),
        .ModelToWorld = ComponentToWorld,
    };

    const size_t TransformationSize = sizeof(FShaderBuffer);

    Data = MetalDevice->newBuffer(
        TransformationSize, MTL::ResourceStorageModeManaged
    );

    std::memcpy(Data->contents(), &BufferData, TransformationSize);
    Data->didModifyRange(NS::Range::Make(0, Data->length()));
}
