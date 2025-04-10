#pragma once

#include "Component.h"
#include "MathFwd.h"
#include "Rotator.h"

struct FRotationData : public Swarm::FComponent
{
    FRotationData(const FRotator& InitialRot) : Rotation(InitialRot){};

    FRotator Rotation;
};
