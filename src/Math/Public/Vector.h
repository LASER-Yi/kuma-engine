#pragma once

template <typename T>
struct alignas(16) TVector
{
    T X;
    T Y;
    T Z;
    T W;
};

using FVector = TVector<float>;

template <typename T>
static TVector<T> operator+(const TVector<T>& lhs, const TVector<T>& rhs)
{
    return {
        .X = lhs.X + rhs.X,
        .Y = lhs.Y + rhs.Y,
        .Z = lhs.Z + rhs.Z,
        .W = lhs.W + rhs.W,
    };
}
