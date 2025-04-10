#include "CoreMinimal.h"
#include "MathFwd.h"
#include <gtest/gtest.h>

TEST(VectorTests, VectorAdd)
{
    const FVector Left = {2.0, 2.0, 2.0};
    const FVector Right = {1.0, 1.0, 1.0};

    const FVector Result = Left + Right;

    ASSERT_FLOAT_EQ(Result.X, 3.0);
    ASSERT_FLOAT_EQ(Result.Y, 3.0);
    ASSERT_FLOAT_EQ(Result.Z, 3.0);
}

TEST(VectorTests, VectorSubtract)
{
    const FVector Left = {2.0, 2.0, 2.0};
    const FVector Right = {1.0, 1.0, 1.0};

    const FVector Result = Left - Right;

    ASSERT_FLOAT_EQ(Result.X, 1.0);
    ASSERT_FLOAT_EQ(Result.Y, 1.0);
    ASSERT_FLOAT_EQ(Result.Z, 1.0);
}

TEST(VectorTests, VectorEqual)
{
    const FVector Left = {1.0, 1.0, 1.0};
    const FVector Right = {1.0, 1.0, 1.0};
    const FVector Another = {1.0, 1.0, 0.0};

    ASSERT_TRUE(Left == Right);
    ASSERT_FALSE(Left == Another);
}

TEST(VectorTests, VectorSqrtLength)
{
    ASSERT_FLOAT_EQ(FVector::Zero.GetLengthSqrt(), 0.0);
    ASSERT_FLOAT_EQ(FVector::Up.GetLengthSqrt(), 1.0);
    ASSERT_FLOAT_EQ(FVector::One.GetLengthSqrt(), 3.0);

    const FVector Case = {1.0, 2.0, 3.0};
    ASSERT_FLOAT_EQ(Case.GetLengthSqrt(), 14.0);
}

TEST(VectorTests, VectorNormalize)
{
    const FVector Cases[] = {
        {1.0, 0.0, 0.0},
        {1.0, 1.0, 0.0},
        {1.0, 1.0, 1.0},
        {114.0, 514.0, 1919.0}
    };

    for (const FVector& Case : Cases)
    {
        ASSERT_FLOAT_EQ(Case.Normalize().GetLength(), 1.0);
    }
}
