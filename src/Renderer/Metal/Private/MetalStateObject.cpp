#include "MetalStateObject.h"

#include <Metal/MTLDevice.hpp>
#include <Metal/MTLLibrary.hpp>
#include <Metal/MTLRenderPipeline.hpp>

FMetalStateObject::FMetalStateObject(
    MTL::Device* Device, const char* Shader, const char* Vertex,
    const char* Fragment
)
{
    NS::AutoreleasePool* Pool = NS::AutoreleasePool::alloc()->init();
    NS::Error* Error = nullptr;

    MTL::Library* Library = Device->newLibrary(
        NS::String::string(Shader, NS::UTF8StringEncoding), nullptr, &Error
    );

    assert(Library);

    MTL::Function* VertexFunc =
        Library->newFunction(NS::String::string(Vertex, NS::UTF8StringEncoding)
        );
    MTL::Function* FragmentFunc = Library->newFunction(
        NS::String::string(Fragment, NS::UTF8StringEncoding)
    );

    MTL::RenderPipelineDescriptor* Desc =
        MTL::RenderPipelineDescriptor::alloc()->init();
    Desc->setVertexFunction(VertexFunc);
    Desc->setFragmentFunction(FragmentFunc);
    Desc->colorAttachments()->object(0)->setPixelFormat(
        MTL::PixelFormatBGRA8Unorm
    );

    MTL::RenderPipelineState* StateObject =
        Device->newRenderPipelineState(Desc, &Error);
    assert(StateObject);

    Data = StateObject;

    VertexFunc->release();
    FragmentFunc->release();
    Desc->release();
    Library->release();

    Pool->release();
}

FMetalStateObject::~FMetalStateObject()
{
    if (Data)
    {
        Data->release();
        Data = nullptr;
    }
}
