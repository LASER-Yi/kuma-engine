#include "D3D12Viewport.h"

#include "D3D12CmdQueue.h"
#include "D3D12Device.h"
#include "D3D12Fence.h"

#include <cassert>

FD3D12Viewport::FD3D12Viewport(
    std::shared_ptr<FD3D12Device> Device, void* InWindowHandle
)
    : WindowHandle(static_cast<HWND>(InWindowHandle)), Width(800), Height(600),
      FrameCount(2)
{
    assert(Device);

    RECT WindowRect;
    if (GetWindowRect(WindowHandle, &WindowRect))
    {
        Width = WindowRect.right - WindowRect.left;
        Height = WindowRect.bottom - WindowRect.top;
    }

    {
        IDXGIFactory* Factory = Device->GetFactory();

        DXGI_SWAP_CHAIN_DESC SwapChainDesc;
        ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

        SwapChainDesc.BufferCount = FrameCount;
        SwapChainDesc.BufferDesc.Width = Width;
        SwapChainDesc.BufferDesc.Height = Height;
        SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        SwapChainDesc.OutputWindow = WindowHandle;
        SwapChainDesc.SampleDesc.Count = 1;
        SwapChainDesc.Windowed = TRUE;

        Microsoft::WRL::ComPtr<IDXGISwapChain> NewSwapChain;
        const HRESULT Result = Factory->CreateSwapChain(
            Device->CmdQueue->GetCommandQueue(), &SwapChainDesc, &NewSwapChain
        );
        assert(SUCCEEDED(Result));

        const bool AssignResult = SUCCEEDED(NewSwapChain.As(&SwapChain));
        assert(AssignResult);
    }

    constexpr DXGI_RGBA Background = {0.0, 0.0, 0.0, 1.0};
    SwapChain->SetBackgroundColor(&Background);
    FrameIndex = SwapChain->GetCurrentBackBufferIndex();

    ID3D12Device* DevicePtr = Device->GetDevice();
    {
        D3D12_DESCRIPTOR_HEAP_DESC RenderTargetHeapDesc;
        ZeroMemory(&RenderTargetHeapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));

        RenderTargetHeapDesc.NumDescriptors = FrameCount;
        RenderTargetHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        RenderTargetHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        const bool Result = SUCCEEDED(DevicePtr->CreateDescriptorHeap(
            &RenderTargetHeapDesc, IID_PPV_ARGS(&RenderTargetHeap)
        ));
        assert(Result);

        RenderTargetDescriptorSize =
            DevicePtr->GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV
            );

        D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetHandle =
            RenderTargetHeap->GetCPUDescriptorHandleForHeapStart();

        for (std::uint32_t i = 0; i < FrameCount; ++i)
        {
            SwapChain->GetBuffer(i, IID_PPV_ARGS(&RenderTargets[i]));
            DevicePtr->CreateRenderTargetView(
                RenderTargets[i].Get(), nullptr, RenderTargetHandle
            );

            RenderTargetHandle.ptr += RenderTargetDescriptorSize;
        }
    }

    {
        FrameFence = std::make_shared<FD3D12Fence>(Device);
    }

    Device->Viewport = this;
}

void FD3D12Viewport::WaitForPreviousFrame(
    std::shared_ptr<FD3D12CmdQueue> CommandQueue
)
{
    FrameFence->Wait(CommandQueue);

    FrameIndex = SwapChain->GetCurrentBackBufferIndex();
}

void FD3D12Viewport::Present()
{
    SwapChain->Present(1, 0);
}

D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Viewport::GetRenderTargetView() const
{
    D3D12_CPU_DESCRIPTOR_HANDLE Handle = RenderTargetHeap->GetCPUDescriptorHandleForHeapStart();
    Handle.ptr += (FrameIndex * RenderTargetDescriptorSize);
    return Handle;
}

D3D12_VIEWPORT FD3D12Viewport::GetViewport() const
{
    return {
        .TopLeftX = 0,
        .TopLeftY = 0,
        .Width = static_cast<float>(Width),
        .Height = static_cast<float>(Height),
        .MinDepth = D3D12_MIN_DEPTH,
        .MaxDepth = D3D12_MAX_DEPTH,
    };
}

D3D12_RECT FD3D12Viewport::GetScissorRect() const
{
    return {
        .left = 0,
        .top = 0,
        .right = static_cast<LONG>(Width),
        .bottom = static_cast<LONG>(Height),
    };
}
