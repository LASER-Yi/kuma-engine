#pragma once

#include "CoreMinimal.h"

#include "Kuma/Systems/KumaSystemBase.h"
#include "StateObject.h"
#include "SystemUpdateContext.h"

#include <memory>

struct FSceneProxy;
struct FStaticMeshData;

class KMeshRenderSystem : public KKumaSystemBase
{
public:
    virtual void Initialize() override;

    virtual void Execute(const Swarm::FSystemUpdateContext& Context) override;

    virtual void Shutdown() override;

protected:
    std::shared_ptr<FSceneProxy> CreateSceneProxy(const FStaticMeshData* Comp
    ) const;

    std::shared_ptr<FStateObject> GlobalStateObject;
};
