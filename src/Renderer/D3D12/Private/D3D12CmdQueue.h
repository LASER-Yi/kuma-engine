#pragma once

#include <d3d12.h>
#include <memory>
#include <wrl/client.h>

struct FD3D12Device;

struct FD3D12CmdQueue
{
    FD3D12CmdQueue(std::shared_ptr<FD3D12Device> Device);

    ID3D12CommandQueue* GetCommandQueue() const;

private:
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
};
