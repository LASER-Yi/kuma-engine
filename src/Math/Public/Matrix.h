#pragma once

#include "Plane.h"
#include "Rotator.h"
#include "Vector.h"

namespace Math
{

template <typename T>
struct alignas(16) TMatrix
{
    static_assert(std::is_floating_point_v<T>, "T must be floating point");
    T M[4][4];

    TMatrix() = default;
    TMatrix(const TMatrix&) = default;
    TMatrix& operator=(const TMatrix&) = default;
    TMatrix(TMatrix&&) = default;
    TMatrix& operator=(TMatrix&&) = default;

    TMatrix(
        const TVector<T>& InX, const TVector<T>& InY, const TVector<T>& InZ,
        const TVector<T>& InW
    );

    TMatrix(
        const TPlane<T>& InX, const TPlane<T>& InY, const TPlane<T>& InZ,
        const TPlane<T>& InW
    );

public:
    TMatrix operator*(const TMatrix& Other) const;
    bool operator==(const TMatrix& Other) const;

public:
    const static TMatrix Identity;

    static TMatrix MakePerspective(TRadians<T> FoV, T Aspect, T Near, T Far);

    static TMatrix MakePosition(const TVector<T>& InPosition);
    static TMatrix MakeScale(const TVector<T>& InScale);
    static TMatrix MakeRotation(
        const EAxis InAxis, const TRadians<T> InRadians
    );
};

} // namespace Math
