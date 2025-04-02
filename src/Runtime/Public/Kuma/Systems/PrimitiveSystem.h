#pragma once

#include "CoreMinimal.h"
#include "Swarm/System.h"

class KPrimitiveSystem : public Swarm::KSystem
{
public:
    virtual void Initialize() override;

    virtual void Execute(float DeltaTime) override;

    virtual void Shutdown() override;
};
