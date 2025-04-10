#include "Renderer.h"
#include "SceneProxy.h"
#include <memory>

void KRenderer::Shutdown() { Proxies.clear(); }

void KRenderer::SetCamera(std::shared_ptr<FCameraSceneProxy> InCameraData)
{
    if (InCameraData)
    {
        CameraData = InCameraData;
    }
}

void KRenderer::Enqueue(std::shared_ptr<FPrimitiveSceneProxy> InProxy)
{
    if (InProxy)
    {
        Proxies[InProxy->Signature] = InProxy;
    }
}
