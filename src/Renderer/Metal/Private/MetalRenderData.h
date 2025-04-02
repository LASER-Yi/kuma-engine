#pragma once

#include <Metal/MTLBuffer.hpp>
#include <Metal/MTLRenderPipeline.hpp>

struct FMetalRenderData
{
    MTL::RenderPipelineState* State;

    std::size_t VertexCount;

    MTL::Buffer* VertexPos;
    MTL::Buffer* VertexColor;
};
