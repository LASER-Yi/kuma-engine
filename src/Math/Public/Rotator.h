#pragma once

#include "Vector.h"

#include <cstdint>

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

    TRadians() : Value(0) {}
    TRadians(TDegrees<T> InDegrees);

    explicit TRadians(T InValue) : Value(InValue) {}

    T Value;
};

template <typename T>
struct TDegrees
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    TDegrees() : Value(0) {}
    TDegrees(TRadians<T> InRadians);

    explicit TDegrees(T InValue) : Value(InValue) {}

    TDegrees<T> operator+(const TDegrees<T>& InDegrees) const
    {
        return TDegrees<T>(Value + InDegrees.Value);
    }
    void operator+=(const TDegrees<T>& InDegrees) { Value += InDegrees.Value; }

    TDegrees<T> operator-(const TDegrees<T>& InDegrees) const
    {
        return TDegrees<T>(Value - InDegrees.Value);
    }
    void operator-=(const TDegrees<T>& InDegrees) { Value -= InDegrees.Value; }

    TDegrees<T> operator*(const TDegrees<T>& InDegrees) const
    {
        return TDegrees<T>(Value * InDegrees.Value);
    }
    void operator*=(const TDegrees<T>& InDegrees) { Value *= InDegrees.Value; }

    TDegrees<T> operator/(const TDegrees<T>& InDegrees) const
    {
        return TDegrees<T>(Value / InDegrees.Value);
    }
    void operator/=(const TDegrees<T>& InDegrees) { Value /= InDegrees.Value; }

    T Value;
};

/**
 * Same as Unreal Engine, The angles are interpreted as intrinsic rotations
 * applied in the order Yaw, then Pitch, then Roll.
 */
template <typename T>
struct alignas(16) TRotator
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    TRotator() = default;
    TRotator(T Pitch, T Yaw, T Roll);
    TRotator(TDegrees<T> Pitch, TDegrees<T> Yaw, TDegrees<T> Roll);

    /** Rotation around the right axis (around Y axis), Looking up and down
     * (0=Straight Ahead, +Up, -Down) */
    TDegrees<T> Pitch;

    /** Rotation around the up axis (around Z axis), Turning around (0=Forward,
     * +Right, -Left)*/
    TDegrees<T> Yaw;

    /** Rotation around the forward axis (around X axis), Tilting your head,
     * (0=Straight, +Clockwise, -CCW) */
    TDegrees<T> Roll;

    TRotator operator+(const TRotator& Other) const;
    void operator+=(const TRotator& Other);

    TRotator operator-(const TRotator& Other) const;
    void operator-=(const TRotator& Other);

    TRotator operator*(TDegrees<T> Other) const;
    void operator*=(TDegrees<T> Other);
};

template <typename T>
struct alignas(16) TQuat
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");

    T X;
    T Y;
    T Z;
    T W;
};

} // namespace Math
