#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Kuma/Entities/KumaWorld.h"

class KKumaEngine : public KEngine
{
    virtual void Initialize() override;
    virtual void Shutdown() override;

private:
    FKumaWorld CurrentWorld;
};
