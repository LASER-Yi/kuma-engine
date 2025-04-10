#pragma once

#include <array>
#include <memory>

#include <d3d12.h>
#include <dxgi1_5.h>
#include <wrl/client.h>

struct FD3D12Fence;
struct FD3D12CmdQueue;
struct FD3D12Device;

struct FD3D12Viewport
{
    static constexpr std::uint32_t MaxFrameCount = 3;

    FD3D12Viewport(std::shared_ptr<FD3D12Device> Device, void* InWindowHandle);

    void WaitForPreviousFrame(std::shared_ptr<FD3D12CmdQueue> CommandQueue);

private:
    Microsoft::WRL::ComPtr<IDXGISwapChain4> SwapChain;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> RenderTargetHeap;

    std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, MaxFrameCount>
        RenderTargets;

    HWND WindowHandle;
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint32_t FrameCount;

    std::uint32_t FrameIndex;

    std::shared_ptr<FD3D12Fence> FrameFence;
};
