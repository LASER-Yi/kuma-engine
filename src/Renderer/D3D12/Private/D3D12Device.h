#pragma once

#include <d3d12.h>
#include <dxgi.h>
#include <wrl/client.h>

#include <memory>

struct FD3D12CmdQueue;

struct FD3D12Device
{
    FD3D12Device(IDXGIFactory* Factory);

    D3D_FEATURE_LEVEL GetFeatureLevel() const;
    ID3D12Device* GetDevice() const;

private:
    bool
    TryCreateDevice(IDXGIFactory* Factory, D3D_FEATURE_LEVEL InFeatureLevel);

    D3D_FEATURE_LEVEL FeatureLevel;
    Microsoft::WRL::ComPtr<ID3D12Device> Device;

    std::shared_ptr<FD3D12CmdQueue> CommandQueue;
};