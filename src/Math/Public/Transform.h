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
    TVector<T> Translation = TVector<T>::Zero;
    TVector<T> Scale = TVector<T>::One;

    TMatrix<T> ToMatrix() const;
};

using FTransform = TTransform<float>;

} // namespace Math
