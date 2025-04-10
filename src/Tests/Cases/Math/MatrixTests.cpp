#include "CoreMinimal.h"
#include "MathFwd.h"

#include <gtest/gtest.h>

TEST(MatrixTests, MatrixMultiply)
{
    const FMatrix One;
    const FMatrix Another;

    const FMatrix Result = One * Another;

    ASSERT_EQ(Result, FMatrix());
}
