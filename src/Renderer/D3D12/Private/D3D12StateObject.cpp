#include "D3D12StateObject.h"

#include "D3D12Device.h"

#include "D3D12Shader.h"

#include <cassert>
#include <d3d12.h>

FD3D12StateObject::FD3D12StateObject(
    std::shared_ptr<FD3D12Device> Device,
    const std::shared_ptr<FD3D12ShaderResource> InShader
)
{
    D3D12_ROOT_SIGNATURE_DESC RootSignatureDesc;
    RootSignatureDesc.NumParameters = 0;
    RootSignatureDesc.pParameters = nullptr;
    RootSignatureDesc.NumStaticSamplers = 0;
    RootSignatureDesc.pStaticSamplers = nullptr;
    RootSignatureDesc.Flags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    Microsoft::WRL::ComPtr<ID3DBlob> SignatureBlob;
    Microsoft::WRL::ComPtr<ID3DBlob> Error;
    D3D12SerializeRootSignature(
        &RootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &SignatureBlob, &Error
    );
    Device->GetDevice()->CreateRootSignature(
        0, SignatureBlob->GetBufferPointer(), SignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(&Signature)
    );

    D3D12_GRAPHICS_PIPELINE_STATE_DESC Desc = {};
    Desc.InputLayout = {
        InShader->InputLayout.data(),
        static_cast<std::uint32_t>(InShader->InputLayout.size())};
    Desc.pRootSignature = Signature.Get();
    Desc.VS = {
        InShader->VertexShader->GetBufferPointer(),
        InShader->VertexShader->GetBufferSize()};
    Desc.PS = {
        InShader->PixelShader->GetBufferPointer(),
        InShader->PixelShader->GetBufferSize()};
    Desc.RasterizerState = {
        .FillMode = D3D12_FILL_MODE_SOLID,
        .CullMode = D3D12_CULL_MODE_BACK,
        .FrontCounterClockwise = FALSE,
        .DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
        .DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        .DepthClipEnable = TRUE,
        .MultisampleEnable = FALSE,
        .AntialiasedLineEnable = FALSE,
        .ForcedSampleCount = 0,
        .ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF};

    const D3D12_RENDER_TARGET_BLEND_DESC DefaultBlendDesc = {
        .BlendEnable = FALSE,
        .LogicOpEnable = FALSE,
        .SrcBlend = D3D12_BLEND_ONE,
        .DestBlend = D3D12_BLEND_ZERO,
        .BlendOp = D3D12_BLEND_OP_ADD,
        .SrcBlendAlpha = D3D12_BLEND_ONE,
        .DestBlendAlpha = D3D12_BLEND_ZERO,
        .BlendOpAlpha = D3D12_BLEND_OP_ADD,
        .LogicOp = D3D12_LOGIC_OP_NOOP,
        .RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL};

    Desc.BlendState = {
        .AlphaToCoverageEnable = FALSE,
        .IndependentBlendEnable = FALSE,
    };

    for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        Desc.BlendState.RenderTarget[i] = DefaultBlendDesc;
    }

    Desc.DepthStencilState.DepthEnable = FALSE;
    Desc.DepthStencilState.StencilEnable = FALSE;
    Desc.SampleMask = UINT_MAX;
    Desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    Desc.NumRenderTargets = 1;
    Desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    Desc.SampleDesc.Count = 1;

    const bool Result = Device->GetDevice()->CreateGraphicsPipelineState(&Desc, IID_PPV_ARGS(&Data));
    assert(Result);
}
