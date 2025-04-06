#pragma once

#include "Vector.h"

namespace Math
{

template <typename T>
struct alignas(16) TMatrix
{
    TVector<T> Columns[4];

    TMatrix<T>() = default;
    TMatrix<T>(const TMatrix<T>&) = default;
    TMatrix<T>& operator=(const TMatrix<T>&) = default;
    TMatrix<T>(TMatrix<T>&&) = default;
    TMatrix<T>& operator=(TMatrix<T>&&) = default;

    TMatrix<T>(
        const TVector<T>& Column_0, const TVector<T>& Column_1,
        const TVector<T>& Column_2, const TVector<T>& Column_3
    );

    TMatrix<T>(
        const TVector<T>& Position, const TVector<T>& Rotation,
        const TVector<T>& Scale
    );

public:
    static TMatrix<T> Identity();
    static TMatrix<T> MakePosition(const TVector<T>& InPosition);
    static TMatrix<T> MakeScale(const TVector<T>& InScale);

public:
    TVector<T> GetPosition() const;
    void SetPosition(const TVector<T>& NewPosition);

    TVector<T> GetRotation() const;
    void SetRotation(const TVector<T>& NewRotation);

    TVector<T> GetScale() const;
    void SetScale(const TVector<T>& NewScale);
};

using FMatrix = TMatrix<float>;

} // namespace Math
