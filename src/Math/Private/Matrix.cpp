#include "Matrix.h"
#include "Vector.h"

namespace Math
{

template <typename T>
TMatrix<T> TMatrix<T>::Identity = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
};

template <typename T>
TMatrix<T>::TMatrix(
    const TVector<T>& Column_0, const TVector<T>& Column_1,
    const TVector<T>& Column_2, const TVector<T>& Column_3
)
    : Columns({Column_0, Column_1, Column_2, Column_3})
{
}

template <typename T>
TMatrix<T> TMatrix<T>::MakePosition(const TVector<T>& InPosition)
{
    return {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {InPosition.X, InPosition.Y, InPosition.Z, 1.0},
    };
}

template <typename T>
TMatrix<T> TMatrix<T>::MakeScale(const TVector<T>& InScale)
{
    return {
        {InScale.X, 0.0, 0.0, 0.0},
        {0.0, InScale.Y, 0.0, 0.0},
        {0.0, 0.0, InScale.Z, 0.0},
        {0.0, 0.0, 0.0, 1.0},
    };
}

} // namespace Math

template struct Math::TMatrix<float>;
