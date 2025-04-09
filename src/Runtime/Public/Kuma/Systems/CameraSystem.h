#pragma once

#include "Kuma/Systems/KumaSystemBase.h"

/**
 * The system for providing camera data to the renderer
 */
class KCameraSystem : public KKumaSystemBase
{
public:
    virtual void Initialize() override;

    virtual void Execute(const Swarm::FSystemUpdateContext& Context) override;

    virtual void Shutdown() override;
};
