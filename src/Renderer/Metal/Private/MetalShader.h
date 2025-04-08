#pragma once

#include "Matrix.h"
#include "MetalDevice.h"
#include "Shader.h"

#include <memory>
#include <simd/simd.h>

namespace MTL
{
class Device;
class Function;
} // namespace MTL

#pragma mark - Metal Shader Type

static_assert(
    sizeof(Math::FMatrix) == sizeof(simd::float4x4),
    "The size of Math::FMatrix should be the same as simd::float4x4"
);

namespace Metal::ShaderType
{

struct FTransformation
{
    Math::FMatrix Perspective;
    Math::FMatrix WorldToCamera;
    Math::FMatrix ModelToWorld;
};

} // namespace Metal::ShaderType

#pragma mark - Metal Shader Resource

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
