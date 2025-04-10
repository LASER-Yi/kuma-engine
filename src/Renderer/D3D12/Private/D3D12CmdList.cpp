#include "D3D12CmdList.h"
#include "D3D12Device.h"
#include "D3D12StateObject.h"

#include <cassert>

FD3D12CmdList::FD3D12CmdList(std::shared_ptr<FD3D12Device> Device): Device(Device)
{
    const bool Result = SUCCEEDED(Device->GetDevice()->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&CommandAllocator)
    ));
    assert(Result);
}

void FD3D12CmdList::Reset()
{
    CommandAllocator->Reset();
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> FD3D12CmdList::GetCommandList(
    std::shared_ptr<FD3D12StateObject> StateObject) const
{
    if (Device.expired())
    {
        return nullptr;
    }

    auto DevicePtr = Device.lock()->GetDevice();

    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList;

    DevicePtr->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandAllocator.Get(), StateObject->Data.Get(), IID_PPV_ARGS(&CommandList));

    return CommandList;
}

ID3D12CommandAllocator* FD3D12CmdList::GetCommandAllocator() const
{
    return CommandAllocator.Get();
}
