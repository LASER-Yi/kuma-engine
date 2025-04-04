#pragma once

#include <memory>

struct FVertexBuffer
{
    virtual ~FVertexBuffer(){};
};

using FVertexBufferRef = std::shared_ptr<FVertexBuffer>;
