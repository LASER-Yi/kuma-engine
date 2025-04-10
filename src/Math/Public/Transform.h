#pragma once

#include "Matrix.h"
#include "Rotator.h"
#include "Vector.h"

namespace Math
{

template <typename T>
struct TTransform
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    TRotator<T> Rotation;
    TVector<T> Translation;
    TVector<T> Scale = {1.0, 1.0, 1.0};

    TMatrix<T> ToMatrix() const;
};

} // namespace Math
