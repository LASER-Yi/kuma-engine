#include "D3D12Renderer.h"

#include "D3D12Shader.h"

#include <cassert>
#include <d3d12.h>
#include <wrl/client.h>

void KD3D12Renderer::Initialize(void* WindowPtr)
{
    ShaderManager = std::make_shared<FD3D12ShaderManager>();

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

const FShaderManager* KD3D12Renderer::GetShaderManager() const
{
    assert(ShaderManager);
    return ShaderManager.get();
}

FStateObjectRef KD3D12Renderer::CreateStateObject(
    const FShaderResourceRef Shader)
{
    return nullptr;
}

FVertexBufferRef KD3D12Renderer::CreateVertexBuffer(
    const std::vector<Math::FVector>& InVertex)
{
    return nullptr;
}

