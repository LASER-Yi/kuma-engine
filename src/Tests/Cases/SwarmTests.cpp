#include "Swarm/Definition.h"
#include "Swarm/Entity.h"
#include "Swarm/SwarmManager.h"
#include <gtest/gtest.h>

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
    Swarm::KManager* Manager = Swarm::KManager::Get();
    FTestEntity Entity = Manager->MakeEntity<FTestEntity>();

    // Check that the entity has a unique ID
    EXPECT_NE(Entity.GetUnderlyingIndex(), Swarm::InvalidIndex);

    Manager->RemoveEntity(Entity);

    // Check that the entity has been removed
    EXPECT_EQ(Entity.GetUnderlyingIndex(), Swarm::InvalidIndex);

    Entity = Manager->MakeEntity<FTestEntity>();

    // Check that the entity has a unique ID
    EXPECT_NE(Entity.GetUnderlyingIndex(), Swarm::InvalidIndex);
}

TEST(SwarmTest, ComponentCreation)
{
    Swarm::KManager* Manager = Swarm::KManager::Get();

    auto Entity = Manager->MakeEntity<FTestEntity>();

    {
        FTestEntity InvalidEntity = FTestEntity(Swarm::InvalidIndex);

        EXPECT_FALSE(
            Manager->AddComponent<FStringTestComponent>(InvalidEntity, "Test")
        );
    }

    {
        EXPECT_EQ(Manager->GetComponent<FStringTestComponent>(Entity), nullptr);

        const char* TestString = "Test Component";
        const char* AnotherTestString = "Another Test Component";
        EXPECT_TRUE(
            Manager->AddComponent<FStringTestComponent>(Entity, TestString)
        );

        EXPECT_FALSE(Manager->AddComponent<FStringTestComponent>(
            Entity, AnotherTestString
        ));

        FStringTestComponent* Component =
            Manager->GetComponent<FStringTestComponent>(Entity);

        // Check that the component was added successfully
        EXPECT_NE(Component, nullptr);

        EXPECT_EQ(Component->Content, TestString);
    }

    {
        EXPECT_EQ(Manager->GetComponent<FIntTestComponent>(Entity), nullptr);

        int TestValue = 42;
        EXPECT_TRUE(Manager->AddComponent<FIntTestComponent>(Entity, TestValue)
        );

        FIntTestComponent* Component =
            Manager->GetComponent<FIntTestComponent>(Entity);

        // Check that the component was added successfully
        EXPECT_NE(Component, nullptr);

        EXPECT_EQ(Component->Value, TestValue);
    }

    {
        EXPECT_NE(Manager->GetComponent<FStringTestComponent>(Entity), nullptr);

        Manager->RemoveComponent<FStringTestComponent>(Entity);

        EXPECT_EQ(Manager->GetComponent<FStringTestComponent>(Entity), nullptr);
    }

    {
        EXPECT_NE(Manager->GetComponent<FIntTestComponent>(Entity), nullptr);

        Manager->RemoveComponent<FIntTestComponent>(Entity);

        EXPECT_EQ(Manager->GetComponent<FIntTestComponent>(Entity), nullptr);
    }
}

TEST(SwarmTest, EntityComponentCreation)
{
    Swarm::KManager* Manager = Swarm::KManager::Get();

    auto Entity = Manager->MakeEntity<FTestEntity>();

    const char* TestString = "Test Component";

    EXPECT_TRUE(Manager->AddComponent<FStringTestComponent>(Entity, TestString)
    );

    Manager->RemoveEntity(Entity);

    // Check that the component was also removed
    EXPECT_EQ(Manager->GetComponentCount<FStringTestComponent>(), 0);
}
