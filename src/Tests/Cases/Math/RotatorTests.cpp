#include "CoreMinimal.h"
#include "MathFwd.h"

#include <gtest/gtest.h>

TEST(RotatorTests, RotatorAdd)
{
    const FRotator Left = {0.0, 0.0, 0.0};
    const FRotator Right = {90.0, 90.0, 90.0};

    const FRotator Result = Left + Right;

    ASSERT_FLOAT_EQ(Result.Pitch.Value, 90.0);
    ASSERT_FLOAT_EQ(Result.Yaw.Value, 90.0);
    ASSERT_FLOAT_EQ(Result.Roll.Value, 90.0);
}