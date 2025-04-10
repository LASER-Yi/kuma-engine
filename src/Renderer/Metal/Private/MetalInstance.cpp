#include "MetalInstance.h"

#include "Metal/MTLResource.hpp"
#include "MetalDevice.h"
#include "MetalShader.h"
#include "SceneProxy.h"

#include <Metal/MTLDevice.hpp>
#include <memory>

FMetalInstanceResource::FMetalInstanceResource(
    std::shared_ptr<KMetalDevice> Device,
    const std::shared_ptr<FPrimitiveSceneProxy> Proxy
)
    : InstanceCount(1)
{
    const size_t InstanceDataSize = sizeof(Metal::ShaderType::FInstanceData);

    Data = Device->Get()->newBuffer(
        InstanceDataSize * InstanceCount, MTL::ResourceStorageModeManaged
    );

    Update(Proxy);
}

FMetalInstanceResource::~FMetalInstanceResource() { Data->release(); }

void FMetalInstanceResource::Update(
    const std::shared_ptr<FPrimitiveSceneProxy> Proxy
)
{
    assert(InstanceCount == 1); // TODO: Instanced draw

    const size_t InstanceDataSize =
        sizeof(Metal::ShaderType::FInstanceData) * InstanceCount;

    const Metal::ShaderType::FInstanceData InstanceData = {
        .ModelToWorld = Proxy->ComponentToWorld
    };

    std::memcpy(Data->contents(), &InstanceData, InstanceDataSize);
    Data->didModifyRange({0, InstanceDataSize});
}
