#include "CoreMinimal.h"
#include <gtest/gtest.h>
#include <memory>

struct FTestEntity : public Swarm::FEntity
{
};

struct FStringTestComponent : public Swarm::IComponent<FStringTestComponent>
{
    std::string Content;

    FStringTestComponent(const std::string& InContent) : Content(InContent) {}
};

struct FIntTestComponent : public Swarm::IComponent<FIntTestComponent>
{
    int Value;

    FIntTestComponent(int InValue) : Value(InValue) {}
};

TEST(SwarmTest, EntityCreation)
{
    // Create an entity
    Swarm::Manager* Manager = Swarm::Manager::Get();
    std::shared_ptr<FTestEntity> Entity = Manager->MakeEntity<FTestEntity>();

    // Check that the entity has a unique ID
    EXPECT_NE(Entity->GetUnderlyingIndex(), Swarm::InvalidIndex);

    Entity.reset();

    Entity = Manager->MakeEntity<FTestEntity>();

    // Check that the entity has a unique ID
    EXPECT_NE(Entity->GetUnderlyingIndex(), Swarm::InvalidIndex);
}

TEST(SwarmTest, ComponentCreation)
{
    Swarm::Manager* Manager = Swarm::Manager::Get();

    std::shared_ptr<FTestEntity> Entity = Manager->MakeEntity<FTestEntity>();

    {
        FTestEntity InvalidEntity = FTestEntity();

        EXPECT_FALSE(InvalidEntity.AddComponent<FStringTestComponent>("Test"));
    }

    {
        EXPECT_EQ(Entity->GetComponent<FStringTestComponent>(), nullptr);

        const char* TestString = "Test Component";
        const char* AnotherTestString = "Another Test Component";
        EXPECT_TRUE(Entity->AddComponent<FStringTestComponent>(TestString));

        EXPECT_FALSE(
            Entity->AddComponent<FStringTestComponent>(AnotherTestString)
        );

        FStringTestComponent* Component =
            Entity->GetComponent<FStringTestComponent>();

        // Check that the component was added successfully
        EXPECT_NE(Component, nullptr);

        EXPECT_EQ(Component->Content, TestString);
    }

    {
        EXPECT_EQ(Entity->GetComponent<FIntTestComponent>(), nullptr);

        int TestValue = 42;
        EXPECT_TRUE(Entity->AddComponent<FIntTestComponent>(TestValue));

        FIntTestComponent* Component =
            Entity->GetComponent<FIntTestComponent>();

        // Check that the component was added successfully
        EXPECT_NE(Component, nullptr);

        EXPECT_EQ(Component->Value, TestValue);
    }

    {
        EXPECT_NE(Entity->GetComponent<FStringTestComponent>(), nullptr);

        Entity->RemoveComponent<FStringTestComponent>();

        EXPECT_EQ(Entity->GetComponent<FStringTestComponent>(), nullptr);
    }

    {
        EXPECT_NE(Entity->GetComponent<FIntTestComponent>(), nullptr);

        Entity->RemoveComponent<FIntTestComponent>();

        EXPECT_EQ(Entity->GetComponent<FIntTestComponent>(), nullptr);
    }
}

TEST(SwarmTest, EntityComponentCreation)
{
    Swarm::Manager* Manager = Swarm::Manager::Get();

    std::shared_ptr<FTestEntity> Entity = Manager->MakeEntity<FTestEntity>();

    const char* TestString = "Test Component";

    EXPECT_TRUE(Entity->AddComponent<FStringTestComponent>(TestString));

    Entity = nullptr;

    // Check that the component was also removed
    EXPECT_EQ(Manager->GetComponentCount<FStringTestComponent>(), 0);
}
