#pragma once

#include "CoreMinimal.h"
#include "Definition.h"

struct FWorldComponent : public Swarm::FComponent
{
    Swarm::SignatureType AssociatedWorld;
};
