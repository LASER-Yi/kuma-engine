#pragma once

#include "CoreMinimal.h"

#include "PipelineState.h"

struct FPrimitiveComponent : public Swarm::FComponent
{
    FPipelineStateObject StateObject;
};
