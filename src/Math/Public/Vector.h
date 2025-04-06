#pragma once

namespace Math
{

/**
 * The engine uses left-hand coordinate system with Z-axis up and X-axis forward
 * The definition is same as the Unreal Engin
 */
template <typename T>
struct alignas(16) TVector
{
    T X;
    T Y;
    T Z;
    T W;

    static TVector<T> Forward();
    static TVector<T> Right();
    static TVector<T> Up();

    TVector<T> operator+(const TVector<T>& rhs);
};

using FVector = TVector<float>;

} // namespace Math
