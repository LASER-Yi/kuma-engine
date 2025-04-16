#include "D3D12Renderer.h"

#include "D3D12CmdList.h"
#include "D3D12CmdQueue.h"
#include "D3D12Device.h"
#include "D3D12Shader.h"
#include "D3D12StateObject.h"
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

    CommandList = std::make_shared<FD3D12CmdList>(Device);
    ShaderManager = std::make_shared<FD3D12ShaderManager>(Device);
}

void KD3D12Renderer::Update()
{
    Viewport->WaitForPreviousFrame(CommandQueue);

    CommandList->Reset();

    for (const auto& [Component, Proxy] : Primitives)
    {
        const auto SharedProxy = Proxy.lock();
        if (SharedProxy == nullptr)
        {
            continue;
        }

        auto StateObject = std::static_pointer_cast<FD3D12StateObject>(SharedProxy->PipelineStateObject);

        auto Cmd = CommandList->GetCommandList(StateObject);

        const D3D12_VIEWPORT D3DViewport = Viewport->GetViewport();
        const D3D12_RECT ScissorRect = Viewport->GetScissorRect();

        Cmd->SetGraphicsRootSignature(StateObject->Signature.Get());
        Cmd->RSSetViewports(1, &D3DViewport);
        Cmd->RSSetScissorRects(1, &ScissorRect);

        D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView = Viewport->GetRenderTargetView();
        Cmd->OMSetRenderTargets(1, &RenderTargetView, FALSE, nullptr);

        const float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        Cmd->ClearRenderTargetView(RenderTargetView, ClearColor, 0, nullptr);

        Cmd->Close();
    }

    Viewport->Present();
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
    std::shared_ptr<FD3D12ShaderResource> D3D12Shader = std::static_pointer_cast<FD3D12ShaderResource>(Shader);

    return std::make_shared<FD3D12StateObject>(Device, D3D12Shader);
}

std::shared_ptr<FMeshRenderResource> KD3D12Renderer::CreateMesh(
    const FMeshResourceDescriptor& InDescriptor
)
{
    return nullptr;
}
