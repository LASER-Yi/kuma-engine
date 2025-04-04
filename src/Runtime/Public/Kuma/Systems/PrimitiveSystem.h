#pragma once

#include "CoreMinimal.h"
#include "StateObject.h"
#include "Swarm/System.h"
#include "VertexBuffer.h"
#include <memory>

struct FSceneProxy;
struct FPrimitiveComponent;

class KPrimitiveSystem : public Swarm::KSystem
{
public:
    virtual void Initialize() override;

    virtual void Execute(float DeltaTime) override;

    virtual void Shutdown() override;

protected:
    std::shared_ptr<FSceneProxy>
    CreateSceneProxy(const FPrimitiveComponent* Comp) const;

    FStateObjectRef GlobalStateObject;
    FVertexBufferRef ColorVertexBuffer;
};
