#pragma once

#include <memory>

#include <d3d12.h>
#include <wrl/client.h>

struct FD3D12StateObject;
struct FD3D12Device;

struct FD3D12CmdList
{
    FD3D12CmdList(std::shared_ptr<FD3D12Device> Device);

    void Reset();

    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList(std::shared_ptr<FD3D12StateObject> StateObject) const;

    ID3D12CommandAllocator* GetCommandAllocator() const;

private:
    std::weak_ptr<FD3D12Device> Device;

    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandAllocator;
};
