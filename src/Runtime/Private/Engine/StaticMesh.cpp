#include "Engine/StaticMesh.h"
#include "MeshResource.h"

FMeshResourceDescriptor FStaticMesh::Describe() const
{
    return {
        .Vertices = {Vertices.data(), Vertices.size()},
        .Indices = {Indices.data(), Indices.size()}
    };
}
