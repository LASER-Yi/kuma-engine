#pragma once

#include "Vector.h"

namespace Math
{

template <typename T>
struct alignas(16) TTransform
{
    T Matrix[4][4];

    TTransform<T>() = default;

    TTransform<T>(
        const TVector<T>& Position, const TVector<T>& Rotation,
        const TVector<T>& Scale
    );

    TVector<T> GetPosition() const;
    void SetPosition(const TVector<T>& NewPosition);

    TVector<T> GetRotation() const;
    void SetRotation(const TVector<T>& NewRotation);

    TVector<T> GetScale() const;
    void SetScale(const TVector<T>& NewScale);
};

using FTransform = TTransform<float>;

} // namespace Math
