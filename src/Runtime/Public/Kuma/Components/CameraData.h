#pragma once

#include "Component.h"
#include "Rotator.h"

struct FCameraData : public Swarm::FComponent
{
    Math::FDegrees FieldOfView;
    float NearClip;
    float FarClip;

    bool bActive;
};
