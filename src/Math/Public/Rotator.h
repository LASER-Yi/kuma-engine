#pragma once

#include "Vector.h"

#include <cstdint>
#include <numbers>

namespace Math
{

enum class EAxis : uint8_t
{
    X,
    Y,
    Z
};

template <typename T>
struct TDegrees;

template <typename T>
struct TRadians
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    static TRadians From(TDegrees<T> InDegrees);

    explicit TRadians(T InValue) : Value(InValue) {}

    T Value;
};

using FRadians = TRadians<float>;
using FVectorRadians = TVector<FRadians>;

template <typename T>
struct TDegrees
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    static TDegrees From(TRadians<T> InRadians);

    explicit TDegrees(T InValue) : Value(InValue) {}

    T Value;
};

using FDegrees = TDegrees<float>;
using FVectorDegrees = TVector<FDegrees>;

template <typename T>
struct alignas(16) TQuat
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    T X;
    T Y;
    T Z;
    T W;
};

using FQuat = TQuat<float>;

} // namespace Math
