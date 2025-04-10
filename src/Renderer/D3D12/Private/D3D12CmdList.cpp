#include "D3D12CmdList.h"
#include "D3D12Device.h"

#include <cassert>

FD3D12CmdList::FD3D12CmdList(std::shared_ptr<FD3D12Device> Device)
{
    const bool Result = SUCCEEDED(Device->GetDevice()->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&CommandAllocator)
    ));
    assert(Result);
}

void FD3D12CmdList::Reset() { CommandAllocator->Reset(); }
