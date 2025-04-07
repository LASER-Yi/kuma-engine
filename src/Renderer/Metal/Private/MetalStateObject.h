#pragma once

#include "MetalShader.h"
#include "StateObject.h"
#include <memory>

namespace MTL
{
class Device;
class RenderPipelineState;
} // namespace MTL

struct FMetalStateObject : public FStateObject
{
    FMetalStateObject(
        MTL::Device* Device,
        const std::shared_ptr<FMetalShaderResource> InShader
    );
    ~FMetalStateObject();

    MTL::RenderPipelineState* Data;
};
