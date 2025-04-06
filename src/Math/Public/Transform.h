#pragma once

#include "Vector.h"

namespace Math
{

template <typename T>
struct alignas(16) TTransform
{
    TVector<T> Rotation;
    TVector<T> Position;
    TVector<T> Scale;
};

using FTransform = TTransform<float>;

} // namespace Math
