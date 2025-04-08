#pragma once

#include "Matrix.h"
#include "StateObject.h"
#include "TransformBuffer.h"
#include "VertexBuffer.h"

struct FSceneProxy
{
    FStateObjectRef PipelineStateObject;

    Math::FMatrix ComponentToWorld;

    FVertexBufferRef VertexBuffer;
    FVertexBufferRef ColorBuffer;
    FTransformBufferRef Transform;

    size_t VertexCount;
};
