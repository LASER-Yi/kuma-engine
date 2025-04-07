#include "Vector.h"
#include <cmath>

namespace Math
{

template <typename T>
const TVector<T> TVector<T>::Zero = {0.0, 0.0, 0.0};

template <typename T>
const TVector<T> TVector<T>::One = {1.0, 1.0, 1.0};

template <typename T>
const TVector<T> TVector<T>::Forward = {1.0, 0.0, 0.0};

template <typename T>
const TVector<T> TVector<T>::Right = {0.0, 1.0, 0.0};

template <typename T>
const TVector<T> TVector<T>::Up = {0.0, 0.0, 1.0};

template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& Rhs) const
{
    return {
        .X = X + Rhs.X,
        .Y = Y + Rhs.Y,
        .Z = Z + Rhs.Z,
    };
}

template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& Rhs) const
{
    return {
        .X = X - Rhs.X,
        .Y = Y - Rhs.Y,
        .Z = Z - Rhs.Z,
    };
}

template <typename T>
bool TVector<T>::operator==(const TVector<T>& Rhs) const
{
    return X == Rhs.X && Y == Rhs.Y && Z == Rhs.Z;
}

template <typename T>
bool TVector<T>::Equal(const TVector<T>& Rhs, T Tolerance) const
{
    // TODO: Implement Tolerance
    return *this == Rhs;
}

template <typename T>
constexpr T TVector<T>::GetLengthSqrt() const
{
    return X * X + Y * Y + Z * Z;
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

    return {X / Length, Y / Length, Z / Length};
}

template struct Math::TVector<float>;

} // namespace Math
