#pragma once

#include "Matrix.h"

#include <memory>

struct FTransformBuffer
{
    Math::FMatrix Perspective;
    Math::FMatrix WorldToCamera;
    Math::FMatrix ModelToWorld;

    virtual ~FTransformBuffer() = default;
};

using FTransformBufferRef = std::shared_ptr<FTransformBuffer>;
