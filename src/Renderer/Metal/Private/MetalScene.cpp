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

    const size_t SceneDataSize = sizeof(Metal::ShaderType::FSceneData);

    Data =
        MetalDevice->newBuffer(SceneDataSize, MTL::ResourceStorageModeManaged);

    std::memset(Data->contents(), 0, SceneDataSize);
    Data->didModifyRange({0, SceneDataSize});
}

FMetalSceneResource::~FMetalSceneResource() { Data->release(); }

void FMetalSceneResource::Update(const FRendererCameraDescriptor& Camera)
{
    const size_t SceneDataSize = sizeof(Metal::ShaderType::FSceneData);

    Metal::ShaderType::FSceneData NewData;

    NewData.Perspective = FMatrix::MakePerspective(
        Camera.FieldOfView, Camera.AspectRatio, Camera.Near, Camera.Far
    );
    NewData.WorldToCamera = Camera.WorldToCamera;

    std::memcpy(Data->contents(), &NewData, SceneDataSize);
    Data->didModifyRange({0, SceneDataSize});
}
