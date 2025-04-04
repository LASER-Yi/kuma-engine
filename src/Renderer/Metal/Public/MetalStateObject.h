#pragma once

#include "StateObject.h"

namespace MTL
{
class Device;
class RenderPipelineState;
} // namespace MTL

struct FMetalStateObject : public FStateObject
{
    FMetalStateObject(
        MTL::Device* Device, const char* Shader, const char* Vertex,
        const char* Fragment
    );
    ~FMetalStateObject();

    MTL::RenderPipelineState* Data;
};
