#pragma once

#include <d3d12.h>
#include <wrl/client.h>

struct FD3D12CmdQueue
{
    FD3D12CmdQueue(ID3D12Device* Device);

private:
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
};
