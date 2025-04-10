#pragma once

#include "MathFwd.h"
#include "MeshResource.h"

#include <memory>
#include <vector>

struct FStaticMesh
{
    std::vector<FVector> Vertices;
    std::vector<FVector> Normals;
    std::vector<std::uint16_t> Indices;

    FMeshResourceDescriptor Describe() const;

public:
    static const std::shared_ptr<FStaticMesh> Cube;
};
