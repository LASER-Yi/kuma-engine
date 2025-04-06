#include "Transform.h"
#include "Vector.h"

namespace Math
{

template <typename T>
TTransform<T>::TTransform(
    const TVector<T>& Column_0, const TVector<T>& Column_1,
    const TVector<T>& Column_2, const TVector<T>& Column_3
)
    : Columns(Column_0, Column_1, Column_2, Column_3)
{
}

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
TTransform<T> TTransform<T>::Identity()
{
    return {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0},
    };
}

template <typename T>
TTransform<T> TTransform<T>::MakePosition(const TVector<T>& InPosition)
{
    return {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {InPosition.X, InPosition.Y, InPosition.Z, 1.0},
    };
}

template <typename T>
TTransform<T> TTransform<T>::MakeScale(const TVector<T>& InScale)
{
    return {
        {InScale.X, 0.0, 0.0, 0.0},
        {0.0, InScale.Y, 0.0, 0.0},
        {0.0, 0.0, InScale.Z, 0.0},
        {0.0, 0.0, 0.0, 1.0},
    };
}

template <typename T>
TVector<T> TTransform<T>::GetPosition() const
{
    return {Columns[3].X, Columns[3].Y, Columns[3].Z, 1.0};
}

template <typename T>
void TTransform<T>::SetPosition(const TVector<T>& NewPosition)
{
    Columns[3].X = NewPosition.X;
    Columns[3].Y = NewPosition.Y;
    Columns[3].Z = NewPosition.Z;
    Columns[3].W = 1.0; // Ensure the W is set to 1.0
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
