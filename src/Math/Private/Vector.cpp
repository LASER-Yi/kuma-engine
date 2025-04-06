#include "Vector.h"

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
TVector<T> TVector<T>::operator+(const TVector<T>& rhs)
{
    return {
        .X = X + rhs.X,
        .Y = Y + rhs.Y,
        .Z = Z + rhs.Z,
        .W = W + rhs.W,
    };
}

template struct Math::TVector<float>;

} // namespace Math
