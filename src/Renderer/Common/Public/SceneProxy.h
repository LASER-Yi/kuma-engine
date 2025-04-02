#pragma once

#include "Vector.h"

#include <vector>

struct FSceneProxy
{
    const char* Shader;
    const char* VertexEntrypoint;
    const char* FragmentEntrypoint;

    std::vector<FVector> Vertices;
    std::vector<FVector> Colors;
};
