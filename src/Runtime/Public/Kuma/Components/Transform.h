#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Swarm/Definition.h"
#include "Swarm/Interfaces/Component.h"

class KTransformComponent : public Swarm::IComponent
{
public:
    static Swarm::ComponentType GetType() { return 0; }

    FVector Position;
    FVector Rotation;
    FVector Scale;
};
