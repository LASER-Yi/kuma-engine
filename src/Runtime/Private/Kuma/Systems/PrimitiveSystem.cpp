#include "Kuma/Systems/PrimitiveSystem.h"

#include "Kuma/Components/Primitive.h"
#include "Kuma/KumaEngine.h"
#include "Renderer.h"
#include "SceneProxy.h"

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

void KPrimitiveSystem::Initialize() {}

void KPrimitiveSystem::Execute(float DeltaTime)
{
    auto Renderer = GetEngine()->GetRenderer();

    for (FPrimitiveComponent& Primitive : GetComponents<FPrimitiveComponent>())
    {
        constexpr std::array<FVector, 3> Vertices = {
            {{0.0f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}, {0.5f, 0.0f, 0.0f}}
        };

        const FSceneProxy Proxy = {
            .Shader = ShaderSrc,
            .VertexEntrypoint = Vertex,
            .FragmentEntrypoint = Fragment,

            .Vertices =
                {Vertices[0] + Primitive.Offset, Vertices[1] + Primitive.Offset,
                 Vertices[2] + Primitive.Offset},

            .Colors = {{1.0, 0.3f, 0.2f}, {0.8f, 1.0, 0.0f}, {0.8f, 0.0f, 1.0}}
        };

        Renderer->Enqueue(Proxy);
    }
}

void KPrimitiveSystem::Shutdown() {}
