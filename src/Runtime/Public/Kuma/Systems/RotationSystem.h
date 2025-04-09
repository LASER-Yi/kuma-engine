#pragma once

#include "Kuma/Systems/KumaSystemBase.h"

class KRotationSystem : public KKumaSystemBase
{
public:
    virtual void Initialize() override;

    virtual void Execute(const Swarm::FSystemUpdateContext& Context) override;

    virtual void Shutdown() override;
};
