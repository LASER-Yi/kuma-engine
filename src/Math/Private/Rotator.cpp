#include "Rotator.h"

#include <numbers>

namespace Math
{

template <typename T>
TRadians<T>::TRadians(TDegrees<T> InDegrees)
    : Value(
          InDegrees.Value * static_cast<T>(std::numbers::pi) /
          static_cast<T>(180.0)
      )
{
}

template <typename T>
TDegrees<T>::TDegrees(TRadians<T> InRadians)
    : Value(
          InRadians.Value * static_cast<T>(180.0) /
          static_cast<T>(std::numbers::pi)
      )
{
}

#pragma mark - TRotator

template <typename T>
TRotator<T>::TRotator(T Pitch, T Yaw, T Roll)
    : Pitch(Pitch), Yaw(Yaw), Roll(Roll)
{
}

template <typename T>
TRotator<T>::TRotator(TDegrees<T> Pitch, TDegrees<T> Yaw, TDegrees<T> Roll)
    : Pitch(Pitch), Yaw(Yaw), Roll(Roll)
{
}

template <typename T>
TRotator<T> TRotator<T>::operator+(const TRotator<T>& Other) const
{
    return {Pitch + Other.Pitch, Yaw + Other.Yaw, Roll + Other.Roll};
}

template <typename T>
void TRotator<T>::operator+=(const TRotator<T>& Other)
{
    Pitch += Other.Pitch;
    Yaw += Other.Yaw;
    Roll += Other.Roll;
}

template <typename T>
TRotator<T> TRotator<T>::operator-(const TRotator<T>& Other) const
{
    return {Pitch - Other.Pitch, Yaw - Other.Yaw, Roll - Other.Roll};
}

template <typename T>
void TRotator<T>::operator-=(const TRotator<T>& Other)
{
    Pitch -= Other.Pitch;
    Yaw -= Other.Yaw;
    Roll -= Other.Roll;
}

template <typename T>
TRotator<T> TRotator<T>::operator*(TDegrees<T> Other) const
{
    return {Pitch * Other, Yaw * Other, Roll * Other};
}

template <typename T>
void TRotator<T>::operator*=(TDegrees<T> Other)
{
    Pitch *= Other;
    Yaw *= Other;
    Roll *= Other;
}

} // namespace Math

template struct Math::TRadians<float>;
template struct Math::TDegrees<float>;
template struct Math::TRotator<float>;
template struct Math::TQuat<float>;
