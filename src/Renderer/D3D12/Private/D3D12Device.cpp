#include "D3D12Device.h"

#include <initializer_list>

#include <cassert>
#include <d3d12.h>
#include <dxgi1_6.h>

FD3D12Device::FD3D12Device()
{
    CreateDXGIFactory1(IID_PPV_ARGS(&Factory));

    for (D3D_FEATURE_LEVEL Feature :
         {D3D_FEATURE_LEVEL_12_2, D3D_FEATURE_LEVEL_12_1,
          D3D_FEATURE_LEVEL_12_0})
    {
        if (TryCreateDevice(Feature))
        {
            FeatureLevel = Feature;
            break;
        }
    }

    assert(Adapter);
    assert(Device);
}

D3D_FEATURE_LEVEL FD3D12Device::GetFeatureLevel() const { return FeatureLevel; }

IDXGIFactory* FD3D12Device::GetFactory() const { return Factory.Get(); }

IDXGIAdapter* FD3D12Device::GetAdapter() const { return Adapter.Get(); }

ID3D12Device* FD3D12Device::GetDevice() const { return Device.Get(); }

bool FD3D12Device::TryCreateDevice(D3D_FEATURE_LEVEL InFeatureLevel)
{
    assert(Factory);

    Microsoft::WRL::ComPtr<IDXGIFactory6> FactoryNew;
    if (SUCCEEDED(Factory->QueryInterface(IID_PPV_ARGS(&FactoryNew))))
    {
        Microsoft::WRL::ComPtr<IDXGIAdapter1> PendingAdapter;
        UINT AdapterIndex = 0;
        const auto EnumAdapter = [&]()
        {
            const bool Result =
                SUCCEEDED(FactoryNew->EnumAdapterByGpuPreference(
                    AdapterIndex, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                    IID_PPV_ARGS(&PendingAdapter)
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
            PendingAdapter->GetDesc1(&Desc);

            if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                continue;
            }

            if (SUCCEEDED(D3D12CreateDevice(
                    PendingAdapter.Get(), InFeatureLevel, IID_PPV_ARGS(&Device)
                )))
            {
                Adapter = PendingAdapter;
                return true;
            }
        }
    }

    if (Device.Get() == nullptr)
    {
        // Fallback creation process
        Microsoft::WRL::ComPtr<IDXGIAdapter> PendingAdapter;
        for (UINT AdapterIndex = 0;
             SUCCEEDED(Factory->EnumAdapters(AdapterIndex, &PendingAdapter));
             ++AdapterIndex)
        {
            DXGI_ADAPTER_DESC Desc;
            PendingAdapter->GetDesc(&Desc);

            if (SUCCEEDED(D3D12CreateDevice(
                    PendingAdapter.Get(), InFeatureLevel, IID_PPV_ARGS(&Device)
                )))
            {
                Adapter = PendingAdapter;
                return true;
            }
        }
    }

    return false;
}
