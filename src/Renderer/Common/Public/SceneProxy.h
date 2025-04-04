#pragma once

#include "StateObject.h"
#include "VertexBuffer.h"
#include <array>

struct FSceneProxy
{
    FStateObjectRef PipelineStateObject;

    std::array<FVertexBufferRef, 8> VertexBuffers;
    size_t VertexBufferCount;

    size_t VertexCount;
};
