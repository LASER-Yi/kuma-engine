#pragma once

#include <d3d12.h>
#include <dxgi.h>
#include <wrl/client.h>

struct FD3D12Viewport;
struct FD3D12CmdQueue;

struct FD3D12Device
{
    FD3D12Device();

    D3D_FEATURE_LEVEL GetFeatureLevel() const;

    IDXGIFactory* GetFactory() const;
    IDXGIAdapter* GetAdapter() const;
    ID3D12Device* GetDevice() const;

    FD3D12CmdQueue* CmdQueue;
    FD3D12Viewport* Viewport;
private:
    bool TryCreateDevice(D3D_FEATURE_LEVEL InFeatureLevel);

    D3D_FEATURE_LEVEL FeatureLevel;

    Microsoft::WRL::ComPtr<IDXGIFactory> Factory;
    Microsoft::WRL::ComPtr<IDXGIAdapter> Adapter;
    Microsoft::WRL::ComPtr<ID3D12Device> Device;
};
