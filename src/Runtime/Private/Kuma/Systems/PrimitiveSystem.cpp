#include "Kuma/Systems/PrimitiveSystem.h"

#include <array>
#include <memory>
#include <vector>

#include "Kuma/Components/Primitive.h"
#include "Kuma/KumaEngine.h"
#include "Renderer.h"
#include "SceneProxy.h"
#include "Vector.h"

const char* ShaderSrc = R"(
    #include <metal_stdlib>
    using namespace metal;

    struct v2f
    {
        float4 position [[position]];
        half3 color;
    };

    v2f vertex vertexMain( uint vertexId [[vertex_id]],
                           device const float3* positions [[buffer(0)]],
                           device const float3* colors [[buffer(1)]] )
    {
        v2f o;
        o.position = float4( positions[ vertexId ], 1.0 );
        o.color = half3 ( colors[ vertexId ] );
        return o;
    }

    half4 fragment fragmentMain( v2f in [[stage_in]] )
    {
        return half4( in.color, 1.0 );
    }
)";

const char* Vertex = "vertexMain";
const char* Fragment = "fragmentMain";

void KPrimitiveSystem::Initialize()
{
    const auto Renderer = GetEngine()->GetRenderer();
    GlobalStateObject =
        Renderer->CreateStateObject(ShaderSrc, Vertex, Fragment);

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
