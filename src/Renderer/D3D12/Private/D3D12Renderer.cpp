#include "D3D12Renderer.h"

#include <d3d12.h>
#include <wrl/client.h>

void KD3D12Renderer::Initialize(void* WindowPtr)
{
#ifdef KUMA_BUILD_DEBUG
    {
        Microsoft::WRL::ComPtr<ID3D12Debug> DebugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
        {
            DebugController->EnableDebugLayer();
        }
    }
#endif
}

void KD3D12Renderer::Update() {}

void KD3D12Renderer::Shutdown() {}

void KD3D12Renderer::Enqueue(const FSceneProxy& InProxy) {}
