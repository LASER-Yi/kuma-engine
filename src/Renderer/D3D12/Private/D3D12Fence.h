#pragma once

#include <memory>
#include <wrl/client.h>

struct FD3D12CmdQueue;
struct FD3D12Device;
struct ID3D12Fence;

struct FD3D12Fence
{
    FD3D12Fence(std::shared_ptr<FD3D12Device> Device);
    ~FD3D12Fence();

    void Wait(std::shared_ptr<FD3D12CmdQueue> CommandQueue);

private:
    Microsoft::WRL::ComPtr<ID3D12Fence> Fence;

    size_t FenceValue = 0;
    HANDLE FenceEvent = nullptr;
};
