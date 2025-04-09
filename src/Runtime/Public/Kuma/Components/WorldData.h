#pragma once

#include "CoreMinimal.h"
#include "Definition.h"

struct FWorldData : public Swarm::FComponent
{
    Swarm::SignatureType AssociatedWorld;
};
