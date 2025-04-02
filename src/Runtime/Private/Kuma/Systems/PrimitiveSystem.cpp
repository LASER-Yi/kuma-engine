#include "Kuma/Systems/PrimitiveSystem.h"

#include "Kuma/Components/Primitive.h"
#include "Kuma/KumaEngine.h"
#include "PipelineState.h"
#include "Renderer.h"

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
        if (Primitive.StateObject.IsValid() == false)
        {
            const FPipelineDefinition Definition = {
                .shader = ShaderSrc,
                .vertexEntrypoint = Vertex,
                .fragmentEntrypoint = Fragment
            };

            Primitive.StateObject = Renderer->PreparePipelineState(Definition);
        }
    }
}

void KPrimitiveSystem::Shutdown()
{
    auto Renderer = GetEngine()->GetRenderer();

    for (FPrimitiveComponent& Primitive : GetComponents<FPrimitiveComponent>())
    {
        if (Primitive.StateObject.IsValid())
        {
            Renderer->ReleasePipelineState(&Primitive.StateObject);
        }
    }
}
