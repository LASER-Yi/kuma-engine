#pragma once

#include "RenderResource.h"

#include <Metal/MTLBuffer.hpp>
#include <memory>

class KMetalDevice;
struct FPrimitiveSceneProxy;

struct FMetalInstanceResource : public FRenderResource
{
    FMetalInstanceResource(
        std::shared_ptr<KMetalDevice> Device,
        const std::shared_ptr<FPrimitiveSceneProxy> Proxy
    );

    ~FMetalInstanceResource();

    void Update(const std::shared_ptr<FPrimitiveSceneProxy> Proxy);

    size_t InstanceCount;
    MTL::Buffer* Data;
};
