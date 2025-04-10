#include "D3D12Shader.h"

#include <cassert>
#include <d3dcompiler.h>

FD3D12ShaderResource::FD3D12ShaderResource(
    std::shared_ptr<FD3D12Device> Device, std::string_view ShaderSrc,
    const char* VertexEntry, const char* PixelEntry
)
{
#if KUMA_BUILD_DEBUG
    std::uint32_t CompileFlags =
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    std::uint32_t CompileFlags = 0;
#endif

    const bool VSResult = SUCCEEDED(D3DCompile(
        ShaderSrc.data(), ShaderSrc.size(), nullptr, nullptr, nullptr,
        VertexEntry, "vs_5_0", CompileFlags, 0, &VertexShader, nullptr
    ));
    assert(VSResult);

    const bool PSResult = SUCCEEDED(D3DCompile(
        ShaderSrc.data(), ShaderSrc.size(), nullptr, nullptr, nullptr,
        PixelEntry, "ps_5_0", CompileFlags, 0, &PixelShader, nullptr
    ));
    assert(PSResult);

    // TODO: Hard-coded layout
    InputLayout = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,
         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};
}

const char* PrimitiveShaderSrc = R"(
    struct PSInput
    {
        float4 position : SV_POSITION;
        float4 color : COLOR;
    };

    PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
    {
        PSInput result;

        result.position = position;
        result.color = color;

        return result;
    }

    float4 PSMain(PSInput input) : SV_TARGET
    {
        return input.color;
    }
)";

FD3D12ShaderManager::FD3D12ShaderManager(std::shared_ptr<FD3D12Device> Device)
{
    std::string_view ShaderSrcView(PrimitiveShaderSrc);
    PrimitiveShader = std::make_shared<FD3D12ShaderResource>(
        Device, ShaderSrcView, "VSMain", "PSMain"
    );
}

FShaderResourceRef FD3D12ShaderManager::GetPrimitive() const
{
    return PrimitiveShader;
}
