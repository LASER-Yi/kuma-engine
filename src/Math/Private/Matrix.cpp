#include "Matrix.h"

#include <cmath>

#include "Vector.h"

namespace Math
{

template <typename T>
const TMatrix<T> TMatrix<T>::Identity = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0},
};

template <typename T>
TMatrix<T>::TMatrix(
    const TVector<T>& InX, const TVector<T>& InY, const TVector<T>& InZ,
    const TVector<T>& InW
)
{
    M[0][0] = InX.X;
    M[0][1] = InX.Y;
    M[0][2] = InX.Z;
    M[0][3] = 0.0;

    M[1][0] = InY.X;
    M[1][1] = InY.Y;
    M[1][2] = InY.Z;
    M[1][3] = 0.0;

    M[2][0] = InZ.X;
    M[2][1] = InZ.Y;
    M[2][2] = InZ.Z;
    M[2][3] = 0.0;

    M[3][0] = InW.X;
    M[3][1] = InW.Y;
    M[3][2] = InW.Z;
    M[3][3] = 1.0;
}

template <typename T>
TMatrix<T> TMatrix<T>::MakePosition(const TVector<T>& InPosition)
{
    return {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {InPosition.X, InPosition.Y, InPosition.Z},
    };
}

template <typename T>
TMatrix<T> TMatrix<T>::MakeScale(const TVector<T>& InScale)
{
    return {
        {InScale.X, 0.0, 0.0},
        {0.0, InScale.Y, 0.0},
        {0.0, 0.0, InScale.Z},
        {0.0, 0.0, 0.0},
    };
}

template <typename T>
TMatrix<T> TMatrix<T>::MakeRotation(const EAxis InAxis, const TDegrees<T> InDegrees)
{
    const T CosValue = std::cos(InDegrees.Value);
    const T SinValue = std::sin(InDegrees.Value);
    if (InAxis == EAxis::X)
    {
        return {
            {1.0, 0.0, 0.0},
            {0.0, CosValue, -SinValue},
            {0.0, SinValue, CosValue},
            {0.0, 0.0, 0.0},
        };
    }
    else if (InAxis == EAxis::Y)
    {
        return {
            {CosValue, 0.0, SinValue},
            {0.0, 1.0, 0.0},
            {-SinValue, 0.0, CosValue},
            {0.0, 0.0, 0.0},
        };
    }
    else if (InAxis == EAxis::Z)
    {
        return {
            {CosValue, -SinValue, 0.0},
            {SinValue, CosValue, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 0.0},
        };
    }
    else
    {
        return Identity;
    }
}

} // namespace Math

template struct Math::TMatrix<float>;
