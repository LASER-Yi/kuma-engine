#pragma once

#include "Shader.h"

#include <d3d12.h>
#include <string_view>
#include <vector>
#include <wrl/client.h>

struct FD3D12Device;

struct FD3D12ShaderResource : public FShaderResource
{
    FD3D12ShaderResource(
        std::shared_ptr<FD3D12Device> Device, std::string_view ShaderSrc,
        const char* VertexEntry, const char* PixelEntry
    );

    Microsoft::WRL::ComPtr<ID3DBlob> VertexShader;
    Microsoft::WRL::ComPtr<ID3DBlob> PixelShader;

    std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout;
};

struct FD3D12ShaderManager : public FShaderManager
{
    FD3D12ShaderManager(std::shared_ptr<FD3D12Device> Device);

    virtual FShaderResourceRef GetPrimitive() const override;

private:
    std::shared_ptr<FD3D12ShaderResource> PrimitiveShader;
};
