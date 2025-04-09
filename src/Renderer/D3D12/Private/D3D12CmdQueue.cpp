#include "D3D12CmdQueue.h"
#include "D3D12Device.h"

#include <cassert>

FD3D12CmdQueue::FD3D12CmdQueue(std::shared_ptr<FD3D12Device> Device)
{
    assert(Device);

    ID3D12Device* DevicePtr = Device->GetDevice();
    assert(DevicePtr);

    D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
    ZeroMemory(&QueueDesc, sizeof(QueueDesc));

    QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    const bool Result = SUCCEEDED(
        DevicePtr->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue))
    );
    assert(Result);

    Device->CmdQueue = this;
}

ID3D12CommandQueue* FD3D12CmdQueue::GetCommandQueue() const
{
    return CommandQueue.Get();
}
