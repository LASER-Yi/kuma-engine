#pragma once
#include "D3D12Device.h"
#include "MeshResource.h"

#include <memory>

struct FD3D12MeshResource
{
    FD3D12MeshResource(
        std::shared_ptr<FD3D12Device> Device,
        const FMeshResourceDescriptor& Desc
    );

    Microsoft::WRL::ComPtr<ID3D12Resource> Resource;
    D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
};
