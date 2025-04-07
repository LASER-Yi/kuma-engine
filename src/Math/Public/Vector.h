#pragma once

#include <type_traits>

namespace Math
{

/**
 * The engine uses left-hand coordinate system with Z-axis up and X-axis forward
 * The definition is same as the Unreal Engin
 */
template <typename T>
struct alignas(16) TVector
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    T X;
    T Y;
    T Z;

    const static TVector Zero;
    const static TVector One;

    const static TVector Forward;
    const static TVector Right;
    const static TVector<T> Up;

    TVector operator+(const TVector& Rhs) const;
    TVector operator-(const TVector& Rhs) const;
    bool operator==(const TVector& Rhs) const;

    bool Equal(const TVector& Rhs, T Tolerance) const;

    constexpr T GetLengthSqrt() const;
    T GetLength() const;

    TVector Normalize() const;
};

using FVector = TVector<float>;

} // namespace Math
