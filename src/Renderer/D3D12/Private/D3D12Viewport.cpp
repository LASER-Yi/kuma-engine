#include "D3D12Viewport.h"

#include "D3D12CmdQueue.h"
#include "D3D12Device.h"

#include <cassert>
#include <dxgi1_4.h>

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

    const HRESULT Result = Factory->CreateSwapChain(
        Device->CmdQueue->GetCommandQueue(), &SwapChainDesc, &SwapChain
    );
    assert(SUCCEEDED(Result));

    Device->Viewport = this;
}
