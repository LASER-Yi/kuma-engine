#include "Kuma/Systems/PrimitiveSystem.h"

#include <memory>
#include <vector>

#include "Kuma/Components/Primitive.h"
#include "Kuma/KumaEngine.h"
#include "Matrix.h"
#include "Renderer.h"
#include "Rotator.h"
#include "SceneProxy.h"
#include "Shader.h"

void KPrimitiveSystem::Initialize()
{
    const auto Renderer = GetEngine()->GetRenderer();
    const auto* Shader = Renderer->GetShaderManager();
    GlobalStateObject = Renderer->CreateStateObject(Shader->GetPrimitive());
}

void KPrimitiveSystem::Execute(float DeltaTime)
{
    auto Renderer = GetEngine()->GetRenderer();

    for (FPrimitiveComponent& Primitive : GetComponents<FPrimitiveComponent>())
    {
        if (Primitive.SceneProxy == nullptr)
        {
            const auto SceneProxy = CreateSceneProxy(&Primitive);
            Primitive.SceneProxy = SceneProxy;
            Renderer->Enqueue(SceneProxy);
        }

        Primitive.YRotation += (DeltaTime * 15.0);
        Primitive.XRotation += (DeltaTime * 10.0);

        const Math::FMatrix Location =
            Math::FMatrix::MakePosition({0.0, 0.0, -10.0});

        const Math::FMatrix YRot = Math::FMatrix::MakeRotation(
            Math::EAxis::Y,
            Math::FRadians::From(Math::FDegrees(Primitive.YRotation))
        );

        const Math::FMatrix XRot = Math::FMatrix::MakeRotation(
            Math::EAxis::X,
            Math::FRadians::From(Math::FDegrees(Primitive.XRotation))
        );

        Primitive.SceneProxy->ComponentToWorld = XRot * YRot * Location;
    }
}

void KPrimitiveSystem::Shutdown() { GlobalStateObject = nullptr; }

std::shared_ptr<FSceneProxy> KPrimitiveSystem::CreateSceneProxy(
    const FPrimitiveComponent* Comp
) const
{
    if (Comp == nullptr)
    {
        return nullptr;
    }

    auto Renderer = GetEngine()->GetRenderer();

    auto SceneProxy = std::make_shared<FSceneProxy>();

    SceneProxy->ComponentToWorld = Math::FMatrix::Identity;

    SceneProxy->VertexCount = Comp->Vertex.size();
    SceneProxy->PipelineStateObject = GlobalStateObject;
    SceneProxy->SceneBuffer = Renderer->CreateSceneResource();
    SceneProxy->VertexBuffer = Renderer->CreateVertexBuffer(Comp->Vertex);
    SceneProxy->ColorBuffer = Renderer->CreateVertexBuffer(Comp->Color);

    return SceneProxy;
}
