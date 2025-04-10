#include "MetalScene.h"
#include "Matrix.h"
#include "MetalDevice.h"
#include "MetalShader.h"
#include "Rotator.h"

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLDevice.hpp>
#include <Metal/MTLResource.hpp>
#include <cstring>
#include <simd/simd.h>

FMetalSceneResource::FMetalSceneResource(std::shared_ptr<KMetalDevice> Device)
{
    MTL::Device* MetalDevice = Device->Get();

    const size_t TransformationSize =
        sizeof(Metal::ShaderType::FTransformation);

    Data = MetalDevice->newBuffer(
        TransformationSize, MTL::ResourceStorageModeManaged
    );

    std::memset(Data->contents(), 0, TransformationSize);
}

FMetalSceneResource::~FMetalSceneResource() { Data->release(); }

void FMetalSceneResource::Update(
    const FRendererCameraDescriptor& Camera,
    const FRendererPrimitiveDescriptor& Primitive
)
{
    const size_t TransformationSize =
        sizeof(Metal::ShaderType::FTransformation);
    NS::Range ModifiedRange = {0, TransformationSize};

    Metal::ShaderType::FTransformation NewData;

    {
        NewData.Perspective = FMatrix::MakePerspective(
            Camera.FieldOfView, Camera.AspectRatio, Camera.Near, Camera.Far
        );
        NewData.WorldToCamera = Camera.WorldToCamera;
    }

    {
        NewData.ModelToWorld = Primitive.ModelToWorld;
    }

    std::memcpy(Data->contents(), &NewData, TransformationSize);
    Data->didModifyRange(ModifiedRange);
}
