#pragma once

#include "PipelineState.h"
#include "Renderer.h"

#include <memory>

class KMetalDevice;
class KMetalViewport;
class KMetalCmdQueue;

class KMetalRenderer : public IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

    virtual FPipelineStateObject
    PreparePipelineState(const FPipelineDefinition& InDefinition) override;

    virtual void ReleasePipelineState(FPipelineStateObject* StateObject
    ) override;

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;
};
