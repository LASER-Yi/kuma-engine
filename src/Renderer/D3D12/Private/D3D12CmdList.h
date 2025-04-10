#pragma once

#include <memory>

#include <d3d12.h>
#include <wrl/client.h>

struct FD3D12Device;

struct FD3D12CmdList
{
    FD3D12CmdList(std::shared_ptr<FD3D12Device> Device);

    void Reset();

private:
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandAllocator;

    Microsoft::WRL::ComPtr<ID3D12CommandList> CommandList;
};
