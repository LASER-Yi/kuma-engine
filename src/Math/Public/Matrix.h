#pragma once

#include "Vector.h"
#include <array>

namespace Math
{

template <typename T>
struct alignas(16) TMatrix
{
    T M[4][4];

    TMatrix() = default;
    TMatrix(const TMatrix&) = default;
    TMatrix& operator=(const TMatrix&) = default;
    TMatrix(TMatrix&&) = default;
    TMatrix& operator=(TMatrix&&) = default;

    TMatrix(
        const TVector<T>& InX, const TVector<T>& InY,
        const TVector<T>& InZ, const TVector<T>& InW
    );

public:
    const static TMatrix Identity;

    static TMatrix MakePosition(const TVector<T>& InPosition);
    static TMatrix MakeScale(const TVector<T>& InScale);
};

using FMatrix = TMatrix<float>;

} // namespace Math
