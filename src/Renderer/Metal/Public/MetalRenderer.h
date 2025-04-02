#pragma once

#include "Renderer.h"
#include "SceneProxy.h"

#include <memory>
#include <span>
#include <vector>

class KMetalDevice;
class KMetalViewport;
class KMetalCmdQueue;

class KMetalRenderer : public IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) override;

    virtual void Update() override;

    virtual void Shutdown() override;

    virtual void Enqueue(const FSceneProxy& InProxy) override;

protected:
    // This needs to be refactor if we have more then 1 render data type
    template <typename T>
    T* AllocateFrameRenderData()
    {
        const size_t DataSize = sizeof(T);

        const size_t CurrentSize = FrameRenderData.size();

        FrameRenderData.resize(CurrentSize + DataSize);

        return reinterpret_cast<T*>(&FrameRenderData[CurrentSize]);
    }

    template <typename T>
    std::span<T> GetFrameRenderData()
    {
        T* Data = reinterpret_cast<T*>(FrameRenderData.data());
        const size_t ElementCount = FrameRenderData.size() / sizeof(T);

        return {Data, ElementCount};
    }

private:
    std::shared_ptr<KMetalDevice> Device;
    std::shared_ptr<KMetalViewport> Viewport;
    std::shared_ptr<KMetalCmdQueue> CommandQueue;

    std::vector<std::byte> FrameRenderData;
};
