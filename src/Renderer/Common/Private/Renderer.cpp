#include "Renderer.h"
#include "SceneProxy.h"
#include <memory>

void KRenderer::Shutdown() { Primitives.clear(); }

void KRenderer::SetCamera(std::shared_ptr<FCameraSceneProxy> InCameraData)
{
    if (InCameraData)
    {
        CameraData = InCameraData;
    }
}

void KRenderer::SetPrimitive(std::shared_ptr<FPrimitiveSceneProxy> InProxy)
{
    if (InProxy)
    {
        Primitives[InProxy->Signature] = InProxy;
    }
}
