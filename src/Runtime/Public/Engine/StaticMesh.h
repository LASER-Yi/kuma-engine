#pragma once

#include "MeshResource.h"
#include "Vector.h"
#include <memory>
#include <vector>

struct FStaticMesh
{
    std::vector<FVector> Vertices;
    std::vector<std::uint16_t> Indices;

    FMeshResourceDescriptor Describe() const;

public:
    // TODO: Convert this to asset
    static const std::shared_ptr<FStaticMesh> Cube();
};
