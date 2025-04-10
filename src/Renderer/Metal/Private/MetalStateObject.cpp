#include "MetalStateObject.h"
#include "Foundation/NSError.hpp"

#include <Metal/MTLDevice.hpp>
#include <Metal/MTLLibrary.hpp>
#include <Metal/MTLRenderPipeline.hpp>

FMetalStateObject::FMetalStateObject(
    MTL::Device* Device, const std::shared_ptr<FMetalShaderResource> InShader
)
    : Shader(InShader)
{
    assert(InShader);
    NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();

    NS::Error* Error = nullptr;

    MTL::RenderPipelineDescriptor* Desc =
        MTL::RenderPipelineDescriptor::alloc()->init();
    Desc->setVertexFunction(Shader->VertexFunction);
    Desc->setFragmentFunction(Shader->FragmentFunction);
    Desc->colorAttachments()->object(0)->setPixelFormat(
        MTL::PixelFormatBGRA8Unorm
    );

    MTL::RenderPipelineState* StateObject =
        Device->newRenderPipelineState(Desc, &Error);
    assert(StateObject);

    Data = StateObject;

    Desc->release();
    Pool->release();
}

FMetalStateObject::~FMetalStateObject() { Data->release(); }
