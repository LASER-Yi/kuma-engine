#include "D3D12Fence.h"

#include "D3D12CmdQueue.h"
#include "D3D12Device.h"

#include <cassert>

FD3D12Fence::FD3D12Fence(std::shared_ptr<FD3D12Device> Device)
{
    const bool Result = SUCCEEDED(Device->GetDevice()->CreateFence(
        0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)
    ));
    assert(Result);

    FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    assert(FenceEvent);
}

FD3D12Fence::~FD3D12Fence() { CloseHandle(FenceEvent); }

void FD3D12Fence::Wait(std::shared_ptr<FD3D12CmdQueue> CommandQueue)
{
    const size_t PrevFence = FenceValue;
    CommandQueue->GetCommandQueue()->Signal(Fence.Get(), PrevFence);
    FenceValue += 1;

    if (Fence->GetCompletedValue() < PrevFence)
    {
        Fence->SetEventOnCompletion(PrevFence, FenceEvent);
        WaitForSingleObject(FenceEvent, INFINITE);
    }
}
