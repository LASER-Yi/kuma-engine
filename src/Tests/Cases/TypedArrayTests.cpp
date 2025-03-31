#include "CoreMinimal.h"
#include "Swarm/Containers/TypedArray.h"
#include "Swarm/Definition.h"

#include <gtest/gtest.h>

struct FBase
{
    virtual ~FBase() { Signature = Swarm::InvalidSignature; }

    Swarm::SignatureType Signature = Swarm::InvalidSignature;
    Swarm::SignatureType GetSignature() const { return Signature; }
};

struct FDerivedOne : public FBase
{
    FDerivedOne(int InValue) : Value(InValue) {}
    int Value;
};

struct FDerivedTwo : public FBase
{
    FDerivedTwo(const char* InString) : String(InString) {}
    const char* String;
};

TEST(TypedArrayTests, BasicFeatures)
{

    TTypedArray<FBase> Array;

    Array.Add<FDerivedOne>(114514);
    Array.Add<FDerivedOne>(1919810);
    Array.Add<FDerivedTwo>("Test Value");

    ASSERT_EQ(Array.Count<FDerivedOne>(), 2);
    ASSERT_EQ(Array.Count<FDerivedTwo>(), 1);
}

struct FDerivedWithDestructor : public FBase
{
    static bool bDestructorCalled;
    ~FDerivedWithDestructor() {}
};

bool FDerivedWithDestructor::bDestructorCalled = false;

TEST(TypedArrayTests, Destructor)
{
    TTypedArray<FBase> Array;

    const auto Handle = Array.Add<FDerivedWithDestructor>();

    ASSERT_EQ(FDerivedWithDestructor::bDestructorCalled, false);

    Array.Remove<FDerivedWithDestructor>(Handle);

    ASSERT_EQ(FDerivedWithDestructor::bDestructorCalled, true);
}
