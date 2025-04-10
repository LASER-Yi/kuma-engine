#pragma once

#include "Kuma/Systems/KumaSystemBase.h"

#include <memory>

struct FCameraData;
struct FCameraSceneProxy;

/**
 * The system for providing camera data to the renderer
 */
class KCameraRenderSystem : public KKumaSystemBase
{
public:
    virtual void Initialize() override;

    virtual void Execute(const Swarm::FSystemUpdateContext& Context) override;

    virtual void Shutdown() override;

protected:
    std::shared_ptr<FCameraSceneProxy> CreateSceneProxy(
        const FCameraData* InData
    ) const;
};
