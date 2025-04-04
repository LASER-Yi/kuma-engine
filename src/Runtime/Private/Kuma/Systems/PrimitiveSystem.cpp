#include "Kuma/Systems/PrimitiveSystem.h"

#include <array>
#include <memory>
#include <vector>

#include "Kuma/Components/Primitive.h"
#include "Kuma/KumaEngine.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Shader.h"
#include "Vector.h"

void KPrimitiveSystem::Initialize()
{
    const auto Renderer = GetEngine()->GetRenderer();
    const auto* Shader = Renderer->GetShaderManager();
    GlobalStateObject = Renderer->CreateStateObject(Shader->GetPrimitive());

    std::vector<FVector> Colors;
    Colors.push_back({1.0, 0.3, 0.2});
    Colors.push_back({0.8, 1.0, 0.0});
    Colors.push_back({0.8, 0.0, 1.0});

    ColorVertexBuffer = Renderer->CreateVertexBuffer(Colors);
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

void KPrimitiveSystem::Shutdown()
{
    GlobalStateObject = nullptr;
    ColorVertexBuffer = nullptr;
}

std::shared_ptr<FSceneProxy>
KPrimitiveSystem::CreateSceneProxy(const FPrimitiveComponent* Comp) const
{
    if (Comp == nullptr)
    {
        return nullptr;
    }

    auto Renderer = GetEngine()->GetRenderer();

    auto SceneProxy = std::make_shared<FSceneProxy>();

    SceneProxy->VertexCount = Comp->Vertex.size();
    SceneProxy->PipelineStateObject = GlobalStateObject;
    SceneProxy->VertexBuffers[0] = Renderer->CreateVertexBuffer(Comp->Vertex);
    SceneProxy->VertexBuffers[1] = ColorVertexBuffer;
    SceneProxy->VertexBufferCount = 2;

    return SceneProxy;
}
