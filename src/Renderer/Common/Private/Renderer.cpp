#include "Renderer.h"
#include "SceneProxy.h"
#include <memory>

void KRenderer::Shutdown() { Proxies.resize(0); }

void KRenderer::Enqueue(std::shared_ptr<FSceneProxy> InProxy)
{
    if (InProxy)
    {
        Proxies.push_back(InProxy);
    }
}
