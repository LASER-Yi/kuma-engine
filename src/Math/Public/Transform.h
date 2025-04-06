#pragma once

#include "Vector.h"

namespace Math
{

template <typename T>
struct alignas(16) TTransform
{
    TVector<T> Columns[4];

    TTransform<T>() = default;
    TTransform<T>(const TTransform<T>&) = default;
    TTransform<T>& operator=(const TTransform<T>&) = default;
    TTransform<T>(TTransform<T>&&) = default;
    TTransform<T>& operator=(TTransform<T>&&) = default;

    TTransform<T>(
        const TVector<T>& Column_0, const TVector<T>& Column_1,
        const TVector<T>& Column_2, const TVector<T>& Column_3
    );

    TTransform<T>(
        const TVector<T>& Position, const TVector<T>& Rotation,
        const TVector<T>& Scale
    );

public:
    static TTransform<T> Identity();
    static TTransform<T> MakePosition(const TVector<T>& InPosition);
    static TTransform<T> MakeScale(const TVector<T>& InScale);

public:
    TVector<T> GetPosition() const;
    void SetPosition(const TVector<T>& NewPosition);

    TVector<T> GetRotation() const;
    void SetRotation(const TVector<T>& NewRotation);

    TVector<T> GetScale() const;
    void SetScale(const TVector<T>& NewScale);
};

using FTransform = TTransform<float>;

} // namespace Math
