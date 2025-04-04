#pragma once

#include "MetalDevice.h"
#include "Shader.h"

#include <memory>

namespace MTL
{
class Device;
class Function;
} // namespace MTL

struct FMetalShaderResource : public FShaderResource
{
    FMetalShaderResource(
        KMetalDeviceRef Device, const char* ShaderSrc, const char* VertexEntry,
        const char* FragmentEntry
    );

    ~FMetalShaderResource();

    MTL::Function* VertexFunction;
    MTL::Function* FragmentFunction;
};

struct FMetalShaderManager : public FShaderManager
{
    FMetalShaderManager(KMetalDeviceRef Device);

    virtual FShaderResourceRef GetPrimitive() const override;

private:
    std::shared_ptr<FMetalShaderResource> PrimitiveShader;
};
