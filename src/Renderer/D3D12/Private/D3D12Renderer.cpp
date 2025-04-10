#include "D3D12Renderer.h"

#include "D3D12CmdQueue.h"
#include "D3D12Device.h"
#include "D3D12Shader.h"
#include "D3D12Viewport.h"

#include <cassert>
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

    Device = std::make_shared<FD3D12Device>();
    CommandQueue = std::make_shared<FD3D12CmdQueue>(Device);
    Viewport = std::make_shared<FD3D12Viewport>(Device, WindowPtr);

    ShaderManager = std::make_shared<FD3D12ShaderManager>(Device);
}

void KD3D12Renderer::Update()
{
    Viewport->WaitForPreviousFrame(CommandQueue);
}

void KD3D12Renderer::Shutdown()
{
    Viewport->WaitForPreviousFrame(CommandQueue);

    Viewport.reset();
    CommandQueue.reset();
    ShaderManager.reset();
    Device.reset();
}

void KD3D12Renderer::Resize(size_t Width, size_t Height) {}

const FShaderManager* KD3D12Renderer::GetShaderManager() const
{
    assert(ShaderManager);
    return ShaderManager.get();
}

std::shared_ptr<FSceneRenderResource> KD3D12Renderer::CreateSceneResource()
{
    return nullptr;
}

std::shared_ptr<FStateObject> KD3D12Renderer::CreateStateObject(
    const FShaderResourceRef Shader
)
{
    return nullptr;
}

std::shared_ptr<FMeshRenderResource> KD3D12Renderer::CreateMesh(
    const FMeshResourceDescriptor& InDescriptor
)
{
    return nullptr;
}
