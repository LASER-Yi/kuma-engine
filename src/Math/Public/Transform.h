#pragma once

#include "Vector.h"
namespace Math
{

template <typename T>
struct TTransform
{
    TVector<T> Position;
    TVector<T> Rotation;
    TVector<T> Scale;
};

using FTransform = TTransform<float>;

} // namespace Math
