#pragma once

namespace Math
{

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
