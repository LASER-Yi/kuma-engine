#pragma once

#include <memory>

#include <d3d12.h>
#include <dxgi.h>
#include <wrl/client.h>

struct FD3D12Device;

struct FD3D12Viewport
{
    FD3D12Viewport(std::shared_ptr<FD3D12Device> Device, void* InWindowHandle);

private:
    Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

    HWND WindowHandle;
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint32_t FrameCount;
};
