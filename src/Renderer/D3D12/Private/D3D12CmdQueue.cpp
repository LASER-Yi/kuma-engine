#include "D3D12CmdQueue.h"

#include <cassert>

FD3D12CmdQueue::FD3D12CmdQueue(ID3D12Device* Device)
{
    assert(Device);

    D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
    QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    const bool Result = SUCCEEDED(Device->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue)));
    assert(Result);
}