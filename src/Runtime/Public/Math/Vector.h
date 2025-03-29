#pragma once

#include "CoreMinimal.h"

template <typename T>
struct TVector
{
    T X;
    T Y;
    T Z;

    TVector() : X(0), Y(0), Z(0) {}
};

using FVector = TVector<float>;
