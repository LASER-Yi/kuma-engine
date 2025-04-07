#include "CoreMinimal.h"
#include <gtest/gtest.h>

TEST(MatrixTests, MatrixMultiply)
{
    const Math::FMatrix One = Math::FMatrix::Identity;
    const Math::FMatrix Another = Math::FMatrix::Identity;

    const Math::FMatrix Result = One * Another;

    ASSERT_EQ(Result, Math::FMatrix::Identity);
}
