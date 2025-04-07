#pragma once

#include "Shader.h"

struct FD3D12ShaderManager : public FShaderManager
{
    virtual FShaderResourceRef GetPrimitive() const override;
};
