#pragma once

#include "Vector.h"
#include <array>

namespace Math
{

template <typename T>
struct alignas(16) TMatrix
{
    std::array<TVector<T>, 4> Columns;

    TMatrix<T>() = default;
    TMatrix<T>(const TMatrix<T>&) = default;
    TMatrix<T>& operator=(const TMatrix<T>&) = default;
    TMatrix<T>(TMatrix<T>&&) = default;
    TMatrix<T>& operator=(TMatrix<T>&&) = default;

    TMatrix<T>(
        const TVector<T>& Column_0, const TVector<T>& Column_1,
        const TVector<T>& Column_2, const TVector<T>& Column_3
    );

public:
    static TMatrix<T> Identity;
    static TMatrix<T> MakePosition(const TVector<T>& InPosition);
    static TMatrix<T> MakeScale(const TVector<T>& InScale);
};

using FMatrix = TMatrix<float>;

} // namespace Math
