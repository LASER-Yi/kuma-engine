#include "Vector.h"
#include <cmath>

namespace Math
{

template <typename T>
TVector<T> TVector<T>::Forward()
{
    return {1.0, 0.0, 0.0, 0.0};
}

template <typename T>
TVector<T> TVector<T>::Right()
{
    return {0.0, 1.0, 0.0, 0.0};
}

template <typename T>
TVector<T> TVector<T>::Up()
{
    return {0.0, 0.0, 1.0, 0.0};
}

template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& rhs) const
{
    return {
        .X = X + rhs.X,
        .Y = Y + rhs.Y,
        .Z = Z + rhs.Z,
        .W = W + rhs.W,
    };
}

template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& rhs) const
{
    return {
        .X = X - rhs.X,
        .Y = Y - rhs.Y,
        .Z = Z - rhs.Z,
        .W = W - rhs.W,
    };
}

template <typename T>
T TVector<T>::GetLengthSqrt() const
{
    return X * X + Y * Y + Z * Z + W * W;
}

template <typename T>
T TVector<T>::GetLength() const
{
    return std::sqrt(GetLengthSqrt());
}

template <typename T>
TVector<T> TVector<T>::Normalize() const
{
    const T Length = GetLength();

    return {X / Length, Y / Length, Z / Length, W / Length};
}

template struct Math::TVector<float>;

} // namespace Math
