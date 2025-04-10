#pragma once

#include "StateObject.h"

#include <d3d12.h>
#include <memory>
#include <wrl/client.h>

struct FD3D12ShaderResource;
struct FD3D12Device;

struct FD3D12StateObject: public FStateObject
{
    FD3D12StateObject(std::shared_ptr<FD3D12Device> Device, const std::shared_ptr<FD3D12ShaderResource> InShader);

    Microsoft::WRL::ComPtr<ID3D12RootSignature> Signature;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> Data;
};
