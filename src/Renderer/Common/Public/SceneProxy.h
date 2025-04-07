#pragma once

#include "Matrix.h"
#include "StateObject.h"
#include "VertexBuffer.h"

struct FSceneProxy
{
    FStateObjectRef PipelineStateObject;

    Math::FMatrix ComponentToWorld;

    FVertexBufferRef VertexBuffer;
    FVertexBufferRef ColorBuffer;

    size_t VertexCount;
};
