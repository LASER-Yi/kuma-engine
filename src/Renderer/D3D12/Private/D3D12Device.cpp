#include "D3D12Device.h"
#include "D3D12CmdQueue.h"

#include <cassert>
#include <d3d12.h>
#include <dxgi1_6.h>

FD3D12Device::FD3D12Device(IDXGIFactory* Factory)
{
    assert(Factory);

    for (D3D_FEATURE_LEVEL Feature :
         {D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1,
          D3D_FEATURE_LEVEL_12_0})
    {
        if (TryCreateDevice(Factory, Feature))
        {
            FeatureLevel = Feature;
            break;
        }
    }

    assert(Device);
    CommandQueue = std::make_shared<FD3D12CmdQueue>(Device.Get());
}

D3D_FEATURE_LEVEL FD3D12Device::GetFeatureLevel() const { return FeatureLevel; }

ID3D12Device* FD3D12Device::GetDevice() const { return Device.Get(); }

bool FD3D12Device::TryCreateDevice(
    IDXGIFactory* Factory, D3D_FEATURE_LEVEL InFeatureLevel
)
{
    assert(Factory);

    Microsoft::WRL::ComPtr<IDXGIFactory6> FactoryNew;
    if (SUCCEEDED(Factory->QueryInterface(IID_PPV_ARGS(&FactoryNew))))
    {
        Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
        UINT AdapterIndex = 0;
        const auto EnumAdapter = [&]()
        {
            const bool Result =
                SUCCEEDED(FactoryNew->EnumAdapterByGpuPreference(
                    AdapterIndex, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                    IID_PPV_ARGS(&Adapter)
                ));

            if (Result)
            {
                AdapterIndex += 1;
            }

            return Result;
        };

        while (EnumAdapter())
        {
            DXGI_ADAPTER_DESC1 Desc;
            Adapter->GetDesc1(&Desc);

            if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                continue;
            }

            if (SUCCEEDED(D3D12CreateDevice(
                Adapter.Get(), InFeatureLevel, IID_PPV_ARGS(&Device)
            )))
            {
                return true;
            }
        }
    }

    if (Device.Get() == nullptr)
    {
        // Fallback creation process
        Microsoft::WRL::ComPtr<IDXGIAdapter> Adapter;
        for (UINT AdapterIndex = 0;
             SUCCEEDED(Factory->EnumAdapters(AdapterIndex, &Adapter));
             ++AdapterIndex)
        {
            DXGI_ADAPTER_DESC Desc;
            Adapter->GetDesc(&Desc);

            if (SUCCEEDED(D3D12CreateDevice(
                Adapter.Get(), InFeatureLevel, IID_PPV_ARGS(&Device)
            )))
            {
                return true;
            }
        }
    }

    return false;
}