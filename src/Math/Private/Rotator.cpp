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

} // namespace Math

template struct Math::TRadians<float>;
template struct Math::TDegrees<float>;
template struct Math::TQuat<float>;
