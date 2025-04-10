#include "Matrix.h"

#include <cmath>
#include <cstring>

#include "Rotator.h"
#include "Vector.h"

namespace Math
{

template <typename T>
TMatrix<T>::TMatrix()
{
    std::memset(M, 0, sizeof(M));
    M[0][0] = 1.0;
    M[1][1] = 1.0;
    M[2][2] = 1.0;
    M[3][3] = 1.0;
}

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
TMatrix<T>::TMatrix(
    const TPlane<T>& InX, const TPlane<T>& InY, const TPlane<T>& InZ,
    const TPlane<T>& InW
)
{
    M[0][0] = InX.X;
    M[0][1] = InX.Y;
    M[0][2] = InX.Z;
    M[0][3] = InX.W;

    M[1][0] = InY.X;
    M[1][1] = InY.Y;
    M[1][2] = InY.Z;
    M[1][3] = InY.W;

    M[2][0] = InZ.X;
    M[2][1] = InZ.Y;
    M[2][2] = InZ.Z;
    M[2][3] = InZ.W;

    M[3][0] = InW.X;
    M[3][1] = InW.Y;
    M[3][2] = InW.Z;
    M[3][3] = InW.W;
}

template <typename T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix& Other) const
{
    // TODO: SIMD
    TMatrix Result;

    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] +
                     M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] +
                     M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] +
                     M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] +
                     M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] +
                     M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] +
                     M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] +
                     M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] +
                     M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] +
                     M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] +
                     M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] +
                     M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] +
                     M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] +
                     M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] +
                     M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] +
                     M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] +
                     M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];

    return Result;
}

template <typename T>
bool TMatrix<T>::operator==(const TMatrix& Other) const
{
    for (int X = 0; X < 4; X++)
    {
        for (int Y = 0; Y < 4; Y++)
        {
            if (M[X][Y] != Other.M[X][Y])
            {
                return false;
            }
        }
    }

    return true;
}

template <typename T>
TMatrix<T> TMatrix<T>::Inverse() const
{
    TMatrix<T> Result;

    T Det[4];

    T Tmp[4][4];

    Tmp[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
    Tmp[0][1] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
    Tmp[0][2] = M[1][2] * M[2][3] - M[1][3] * M[2][2];

    Tmp[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
    Tmp[1][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
    Tmp[1][2] = M[0][2] * M[2][3] - M[0][3] * M[2][2];

    Tmp[2][0] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
    Tmp[2][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
    Tmp[2][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

    Tmp[3][0] = M[1][2] * M[2][3] - M[1][3] * M[2][2];
    Tmp[3][1] = M[0][2] * M[2][3] - M[0][3] * M[2][2];
    Tmp[3][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

    Det[0] = M[1][1] * Tmp[0][0] - M[2][1] * Tmp[0][1] + M[3][1] * Tmp[0][2];
    Det[1] = M[0][1] * Tmp[1][0] - M[2][1] * Tmp[1][1] + M[3][1] * Tmp[1][2];
    Det[2] = M[0][1] * Tmp[2][0] - M[1][1] * Tmp[2][1] + M[3][1] * Tmp[2][2];
    Det[3] = M[0][1] * Tmp[3][0] - M[1][1] * Tmp[3][1] + M[2][1] * Tmp[3][2];

    const T Determinant = M[0][0] * Det[0] - M[1][0] * Det[1] +
                          M[2][0] * Det[2] - M[3][0] * Det[3];

    if (Determinant == 0.0 || std::isinf(Determinant))
    {
        return TMatrix<T>();
    }

    const T RDet = 1.0 / Determinant;

    Result.M[0][0] = RDet * Det[0];
    Result.M[0][1] = -RDet * Det[1];
    Result.M[0][2] = RDet * Det[2];
    Result.M[0][3] = -RDet * Det[3];
    Result.M[1][0] = -RDet * (M[1][0] * Tmp[0][0] - M[2][0] * Tmp[0][1] +
                              M[3][0] * Tmp[0][2]);
    Result.M[1][1] = RDet * (M[0][0] * Tmp[1][0] - M[2][0] * Tmp[1][1] +
                             M[3][0] * Tmp[1][2]);
    Result.M[1][2] = -RDet * (M[0][0] * Tmp[2][0] - M[1][0] * Tmp[2][1] +
                              M[3][0] * Tmp[2][2]);
    Result.M[1][3] = RDet * (M[0][0] * Tmp[3][0] - M[1][0] * Tmp[3][1] +
                             M[2][0] * Tmp[3][2]);
    Result.M[2][0] = RDet * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                             M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
                             M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]));
    Result.M[2][1] =
        -RDet * (M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                 M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
                 M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]));
    Result.M[2][2] = RDet * (M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
                             M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
                             M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));
    Result.M[2][3] =
        -RDet * (M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
                 M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
                 M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));
    Result.M[3][0] =
        -RDet * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                 M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
                 M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]));
    Result.M[3][1] = RDet * (M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                             M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
                             M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]));
    Result.M[3][2] =
        -RDet * (M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
                 M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
                 M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
    Result.M[3][3] = RDet * (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
                             M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
                             M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));

    return Result;
}

template <typename T>
TMatrix<T> TMatrix<T>::MakePerspective(TRadians<T> FoV, T Aspect, T Near, T Far)
{
    const T ValueY = 1.0 / std::tan(FoV.Value / 2.0);
    const T ValueX = ValueY / Aspect;
    const T ValueZ = Far / (Near - Far);

    return {
        {ValueX, 0.0, 0.0, 0.0},
        {0.0, ValueY, 0.0, 0.0},
        {0.0, 0.0, ValueZ, -1.0},
        {0.0, 0.0, Near * ValueZ, 0.0}
    };
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

template <typename T>
TMatrix<T> TMatrix<T>::MakeRotation(
    const EAxis InAxis, const TRadians<T> InRadians
)
{
    const T CosValue = std::cos(InRadians.Value);
    const T SinValue = std::sin(InRadians.Value);
    if (InAxis == EAxis::X)
    {
        return {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, CosValue, -SinValue, 0.0},
            {0.0, SinValue, CosValue, 0.0},
            {0.0, 0.0, 0.0, 1.0},
        };
    }
    else if (InAxis == EAxis::Y)
    {
        return {
            {CosValue, 0.0, -SinValue, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {SinValue, 0.0, CosValue, 0.0},
            {0.0, 0.0, 0.0, 1.0},
        };
    }
    else if (InAxis == EAxis::Z)
    {
        return {
            {CosValue, -SinValue, 0.0, 0.0},
            {SinValue, CosValue, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0},
        };
    }
    else
    {
        return {};
    }
}

} // namespace Math

template struct Math::TMatrix<float>;
