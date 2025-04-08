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
#include "Transform.h"

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

    const Math::FMatrix YRot = Math::FMatrix::MakeRotation(
        Math::EAxis::Y, Math::FRadians::From(Math::FDegrees(30.0))
    );

    const Math::FMatrix XRot = Math::FMatrix::MakeRotation(
        Math::EAxis::X, Math::FRadians::From(Math::FDegrees(30.0))
    );

    SceneProxy->ComponentToWorld = XRot * YRot * Math::FMatrix::Identity;

    SceneProxy->VertexCount = Comp->Vertex.size();
    SceneProxy->PipelineStateObject = GlobalStateObject;
    SceneProxy->VertexBuffer = Renderer->CreateVertexBuffer(Comp->Vertex);
    SceneProxy->ColorBuffer = Renderer->CreateVertexBuffer(Comp->Color);

    return SceneProxy;
}
