#include "Transform.h"
#include "Vector.h"

namespace Math
{

template <typename T>
TTransform<T>::TTransform(
    const TVector<T>& Position, const TVector<T>& Rotation,
    const TVector<T>& Scale
)
{
    SetPosition(Position);
    SetRotation(Rotation);
    SetScale(Scale);
}

template <typename T>
TVector<T> TTransform<T>::GetPosition() const
{
    // TODO
    return TVector<T>();
}

template <typename T>
void TTransform<T>::SetPosition(const TVector<T>& NewPosition)
{
    // TODO
}

template <typename T>
TVector<T> TTransform<T>::GetRotation() const
{
    // TODO
    return TVector<T>();
}

template <typename T>
void TTransform<T>::SetRotation(const TVector<T>& NewRotation)
{
}

template <typename T>
TVector<T> TTransform<T>::GetScale() const
{
    // TODO
    return TVector<T>();
}

template <typename T>
void TTransform<T>::SetScale(const TVector<T>& NewScale)
{
    // TODO
}

} // namespace Math

template struct Math::TTransform<float>;
