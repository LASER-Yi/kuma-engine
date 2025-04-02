#pragma once

#include "CoreMinimal.h"

#include "Swarm/Component.h"
#include "Vector.h"

struct FPrimitiveComponent : public Swarm::FComponent
{
    FPrimitiveComponent(const FVector& InOffset)
        : Swarm::FComponent(), Offset(InOffset)
    {
    }

    FVector Offset;
};
