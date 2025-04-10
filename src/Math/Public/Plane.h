#pragma once

#include "Vector.h"

#include <type_traits>

namespace Math
{

template <typename T>
struct alignas(16) TPlane : TVector<T>
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    TPlane() = default;
    TPlane(T InX, T InY, T InZ, T InW) : TVector<T>(InX, InY, InZ), W(InW) {}

    T W;
};

} // namespace Math
