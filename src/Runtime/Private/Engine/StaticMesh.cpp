#include "Engine/StaticMesh.h"
#include "MeshResource.h"

#include <memory>

constexpr float Unit = 0.5;

const std::shared_ptr<FStaticMesh> FStaticMesh::Cube()
{
    static FStaticMesh CubeMesh = {
        .Vertices =
            {
                {
                    -Unit,
                    -Unit,
                    +Unit,
                },
                {+Unit, -Unit, +Unit},
                {+Unit, +Unit, +Unit},
                {-Unit, +Unit, +Unit},
                {-Unit, -Unit, -Unit},
                {-Unit, +Unit, -Unit},
                {+Unit, +Unit, -Unit},
                {+Unit, -Unit, -Unit},
            },
        .Indices = {
            0, 1, 2, 2, 3,
            0, // Front
            1, 7, 6, 6, 2,
            1, // Right
            7, 4, 5, 5, 6,
            7, // Back
            4, 0, 3, 3, 5,
            4, // Left
            3, 2, 6, 6, 5,
            3, // Top
            4, 7, 1, 1, 0,
            4 // Bottom
        }};

    return std::make_shared<FStaticMesh>(CubeMesh);
}

FMeshResourceDescriptor FStaticMesh::Describe() const
{
    return {
        .Vertices = {Vertices.data(), Vertices.size()},
        .Indices = {Indices.data(), Indices.size()}};
}
