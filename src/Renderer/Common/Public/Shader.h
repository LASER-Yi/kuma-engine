#pragma once

#include "RenderResource.h"
#include <memory>

/**
 @brief The shader to use with the PSO.
 @note Currently, we only have hard-coded shaders for each platforms
 */
struct FShaderResource : public FRenderResource
{
};

using FShaderResourceRef = std::shared_ptr<FShaderResource>;

struct FShaderManager
{
    virtual ~FShaderManager() = default;

    virtual FShaderResourceRef GetPrimitive() const = 0;
};
