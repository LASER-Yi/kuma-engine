#include "Transform.h"
#include "Matrix.h"
#include "Rotator.h"

namespace Math
{

template <typename T>
TMatrix<T> TTransform<T>::ToMatrix() const
{
    const TMatrix<T> TranslationMatrix = TMatrix<T>::MakePosition(Translation);
    const TMatrix<T> YawRotationMatrix =
        TMatrix<T>::MakeRotation(EAxis::Z, Rotation.Yaw);
    const TMatrix<T> PitchRotationMatrix =
        TMatrix<T>::MakeRotation(EAxis::Y, Rotation.Pitch);
    const TMatrix<T> RollRotationMatrix =
        TMatrix<T>::MakeRotation(EAxis::X, Rotation.Roll);
    const TMatrix<T> ScaleMatrix = TMatrix<T>::MakeScale(Scale);

    return ScaleMatrix * YawRotationMatrix * PitchRotationMatrix *
           RollRotationMatrix * TranslationMatrix;
}

} // namespace Math

template struct Math::TTransform<float>;
