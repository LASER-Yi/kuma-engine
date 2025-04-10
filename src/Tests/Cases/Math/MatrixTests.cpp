#include "CoreMinimal.h"
#include "MathFwd.h"

#include <gtest/gtest.h>

TEST(MatrixTests, MatrixMultiply)
{
    const FMatrix One = FMatrix::Identity;
    const FMatrix Another = FMatrix::Identity;

    const FMatrix Result = One * Another;

    ASSERT_EQ(Result, FMatrix::Identity);
}
