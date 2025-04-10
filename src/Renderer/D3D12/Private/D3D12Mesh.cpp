#include "D3D12Mesh.h"

#include <cassert>

FD3D12MeshResource::FD3D12MeshResource(
    std::shared_ptr<FD3D12Device> Device, const FMeshResourceDescriptor& Desc
)
{
    const UINT VertexBufferSize = Desc.Vertices.size_bytes();

    D3D12_HEAP_PROPERTIES HeapProperties = {};
    HeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    HeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    HeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    HeapProperties.CreationNodeMask = 1;
    HeapProperties.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC ResourceDesc = {};
    ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    ResourceDesc.Alignment = 16;
    ResourceDesc.Width = VertexBufferSize;
    ResourceDesc.Height = 1;
    ResourceDesc.DepthOrArraySize = 1;
    ResourceDesc.MipLevels = 1;
    ResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    ResourceDesc.SampleDesc.Count = 1;
    ResourceDesc.SampleDesc.Quality = 0;
    ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    ResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    const bool Result = SUCCEEDED(Device->GetDevice()->CreateCommittedResource(
        &HeapProperties, D3D12_HEAP_FLAG_NONE, &ResourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource)
    ));
    assert(Result);

    UINT8* DataPtr = nullptr;
    D3D12_RANGE ReadRange = {};
    ReadRange.Begin = 0;
    ReadRange.End = 0;

    Resource->Map(0, &ReadRange, reinterpret_cast<void**>(&DataPtr));
    std::memcpy(DataPtr, Desc.Vertices.data(), VertexBufferSize);

    VertexBufferView.BufferLocation = Resource->GetGPUVirtualAddress();
    VertexBufferView.SizeInBytes = VertexBufferSize;
    VertexBufferView.StrideInBytes = VertexBufferSize;
}
