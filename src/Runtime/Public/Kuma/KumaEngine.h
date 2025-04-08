#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Kuma/Entities/KumaWorld.h"

#include <memory>

class KKumaEngine : public KEngine
{
    virtual void Initialize(const FEngineInitializationContext& Context
    ) override;
    virtual void Shutdown() override;

private:
    std::shared_ptr<FKumaWorld> CurrentWorld;
};
