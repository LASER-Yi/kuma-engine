#include "Engine/StaticMesh.h"
#include "MathFwd.h"

#include <memory>

constexpr float s = 0.5;

const std::shared_ptr<FStaticMesh>
    FStaticMesh::Cube =
        std::make_shared<FStaticMesh>(
            FStaticMesh{
                .Vertices =
                    {
                        // front
                        {+s, +s, +s},
                        {+s, +s, -s},
                        {+s, -s, -s},
                        {+s, -s, +s},
                        // right
                        {+s, -s, +s},
                        {+s, -s, -s},
                        {-s, -s, -s},
                        {-s, -s, +s},
                        // back
                        {-s, -s, +s},
                        {-s, -s, -s},
                        {-s, +s, -s},
                        {-s, +s, +s},
                        // left
                        {-s, +s, +s},
                        {-s, +s, -s},
                        {+s, +s, -s},
                        {+s, +s, +s},
                        // top
                        {+s, -s, +s},
                        {-s, -s, +s},
                        {-s, +s, +s},
                        {+s, +s, +s},
                        // bottom
                        {+s, +s, -s},
                        {-s, +s, -s},
                        {-s, -s, -s},
                        {+s, -s, -s},
                    },
                .Normals =
                    {
                        // front
                        FVector::Forward,
                        FVector::Forward,
                        FVector::Forward,
                        FVector::Forward,
                        // right
                        FVector::Right,
                        FVector::Right,
                        FVector::Right,
                        FVector::Right,
                        // back
                        -FVector::Forward,
                        -FVector::Forward,
                        -FVector::Forward,
                        -FVector::Forward,
                        // left
                        -FVector::Right,
                        -FVector::Right,
                        -FVector::Right,
                        -FVector::Right,
                        // top
                        FVector::Up,
                        FVector::Up,
                        FVector::Up,
                        FVector::Up,
                        // bottom
                        -FVector::Up,
                        -FVector::Up,
                        -FVector::Up,
                        -FVector::Up,
                    },
                .Indices =
                    {// front
                     0, 1, 2, 2, 3, 0,
                     // right
                     4, 5, 6, 6, 7, 4,
                     // back
                     8, 9, 10, 10, 11, 8,
                     // left
                     12, 13, 14, 14, 15, 12,
                     // top
                     16, 17, 18, 18, 19, 16,
                     // bottom
                     20, 21, 22, 22, 23, 20
                    }
            }
        );
