#pragma once

#include "Component.h"
#include "Rotator.h"

#include <memory>

struct FCameraSceneProxy;

struct FCameraData : public Swarm::FComponent
{
    Math::FDegrees FieldOfView = Math::FDegrees(60.0);
    float NearClip = 0.01;
    float FarClip = 100.0;

    bool bActive;

    std::shared_ptr<FCameraSceneProxy> SceneProxy;
};
