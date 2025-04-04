#include "MetalShader.h"
#include "Foundation/NSAutoreleasePool.hpp"
#include "MetalDevice.h"
#include "Shader.h"

#include <Metal/MTLDevice.hpp>
#include <Metal/MTLLibrary.hpp>
#include <cassert>
#include <memory>

FMetalShaderResource::FMetalShaderResource(
    KMetalDeviceRef Device, const char* ShaderSrc, const char* VertexEntry,
    const char* FragmentEntry
)
{
    NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();

    NS::Error* Error = nullptr;

    MTL::Library* Library = Device->Get()->newLibrary(
        NS::String::string(ShaderSrc, NS::UTF8StringEncoding), nullptr, &Error
    );

    assert(Library);

    VertexFunction = Library->newFunction(
        NS::String::string(VertexEntry, NS::UTF8StringEncoding)
    );

    FragmentFunction = Library->newFunction(
        NS::String::string(FragmentEntry, NS::UTF8StringEncoding)
    );

    Library->release();
    Pool->release();
}

FMetalShaderResource::~FMetalShaderResource()
{
    VertexFunction->release();
    VertexFunction = nullptr;

    FragmentFunction->release();
    FragmentFunction = nullptr;
}

#pragma mark - Shader

const char* PrimitiveShaderSrc = R"(
    #include <metal_stdlib>
    using namespace metal;

    struct v2f
    {
        float4 position [[position]];
        half3 color;
    };

    v2f vertex vertexMain( uint vertexId [[vertex_id]],
                           device const float3* positions [[buffer(0)]],
                           device const float3* colors [[buffer(1)]] )
    {
        v2f o;
        o.position = float4( positions[ vertexId ], 1.0 );
        o.color = half3 ( colors[ vertexId ] );
        return o;
    }

    half4 fragment fragmentMain( v2f in [[stage_in]] )
    {
        return half4( in.color, 1.0 );
    }
)";

const char* PrimitiveVertex = "vertexMain";
const char* PrimitiveFragment = "fragmentMain";

#pragma mark - FMetalShaderManager

FMetalShaderManager::FMetalShaderManager(KMetalDeviceRef Device)
{
    PrimitiveShader = std::make_shared<FMetalShaderResource>(
        Device, PrimitiveShaderSrc, PrimitiveVertex, PrimitiveFragment
    );
}

FShaderResourceRef FMetalShaderManager::GetPrimitive() const
{
    return PrimitiveShader;
}
