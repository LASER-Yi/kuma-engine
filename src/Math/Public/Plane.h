#pragma once

#include <type_traits>

namespace Math
{

template <typename T>
struct alignas(16) TPlane
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    TPlane() = default;
    TPlane(T InX, T InY, T InZ, T InW) : X(InX), Y(InY), Z(InZ), W(InW) {}

    T X;
    T Y;
    T Z;
    T W;
};

using FPlane = TPlane<float>;

} // namespace Math
