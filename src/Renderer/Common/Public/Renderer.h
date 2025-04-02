#pragma once

#include "PipelineState.h"

class IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown() = 0;

    virtual FPipelineStateObject
    PreparePipelineState(const FPipelineDefinition& InDefinition) = 0;

    virtual void ReleasePipelineState(FPipelineStateObject* StateObject) = 0;
};
