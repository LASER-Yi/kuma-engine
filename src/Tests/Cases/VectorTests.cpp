#include "Vector.h"
#include <gtest/gtest.h>

TEST(VectorTests, VectorAdd)
{
    const Math::FVector Left = {2.0, 2.0, 2.0, 2.0};
    const Math::FVector Right = {1.0, 1.0, 1.0, 1.0};

    const Math::FVector Result = Left + Right;

    ASSERT_EQ(Result.X, 3.0);
    ASSERT_EQ(Result.Y, 3.0);
    ASSERT_EQ(Result.Z, 3.0);
    ASSERT_EQ(Result.W, 3.0);
}

TEST(VectorTests, VectorSubtract)
{
    const Math::FVector Left = {2.0, 2.0, 2.0, 2.0};
    const Math::FVector Right = {1.0, 1.0, 1.0, 1.0};

    const Math::FVector Result = Left - Right;

    ASSERT_EQ(Result.X, 1.0);
    ASSERT_EQ(Result.Y, 1.0);
    ASSERT_EQ(Result.Z, 1.0);
    ASSERT_EQ(Result.W, 1.0);
}
