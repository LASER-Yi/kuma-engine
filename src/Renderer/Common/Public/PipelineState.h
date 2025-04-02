#pragma once

struct FPipelineDefinition
{
    const char* shader;

    const char* vertexEntrypoint;
    const char* fragmentEntrypoint;
};

struct FPipelineStateObject
{
    void* Data;

    bool IsValid() const { return Data != nullptr; }
};
