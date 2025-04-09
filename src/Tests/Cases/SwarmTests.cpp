#include "CoreMinimal.h"
#include "Definition.h"
#include "Entity.h"
#include <gtest/gtest.h>
#include <memory>

struct FContentComponent : public Swarm::FComponent
{
    std::string Content;

    FContentComponent(const std::string& InContent) : Content(InContent) {}
};

struct FExternalComponent : public Swarm::FComponent
{
    int Value;

    FExternalComponent(int InValue) : Value(InValue) {}
};

struct FTestEntity : public Swarm::FEntity
{
    FTestEntity(
        Swarm::FEntityInitializationContext& Context, const std::string& Content
    )
        : Swarm::FEntity(Context)
    {
        Context.CreateDefaultComponent<FContentComponent>(Content);
    }
};

TEST(SwarmTests, EntityCreation)
{
    // Create an entity
    const char* TestContent = "Test Component";
    Swarm::Manager* Manager = Swarm::Manager::Get();
    std::shared_ptr<FTestEntity> Entity =
        Manager->MakeEntity<FTestEntity>(TestContent);

    // Check that the entity has a unique ID
    EXPECT_NE(Entity->Signature, Swarm::InvalidSignature);

    // Check that the entity has the required component
    EXPECT_NE(Entity->GetComponent<FContentComponent>(), nullptr);
    EXPECT_EQ(Entity->GetComponent<FContentComponent>()->Content, TestContent);

    Entity = nullptr;

    // Destroy entity should destroy all of its components
    EXPECT_EQ(Manager->GetComponentCount<FContentComponent>(), 0);
}

TEST(SwarmTests, ComponentCreation)
{
    const char* TestContent = "Test Component";
    Swarm::Manager* Manager = Swarm::Manager::Get();

    std::shared_ptr<FTestEntity> Entity =
        Manager->MakeEntity<FTestEntity>(TestContent);

    {
        const char* AnotherTestContent = "Another Test Component";
        EXPECT_FALSE(Entity->AddComponent<FContentComponent>(AnotherTestContent)
        );
    }

    {
        EXPECT_EQ(Entity->GetComponent<FExternalComponent>(), nullptr);

        int TestValue = 42;
        EXPECT_TRUE(Entity->AddComponent<FExternalComponent>(TestValue));

        FExternalComponent* Component =
            Entity->GetComponent<FExternalComponent>();

        // Check that the component was added successfully
        EXPECT_NE(Component, nullptr);

        EXPECT_EQ(Component->Value, TestValue);
    }

    {
        EXPECT_NE(Entity->GetComponent<FContentComponent>(), nullptr);

        Entity->RemoveComponent<FContentComponent>();

        EXPECT_EQ(Entity->GetComponent<FContentComponent>(), nullptr);
    }

    {
        EXPECT_NE(Entity->GetComponent<FExternalComponent>(), nullptr);

        Entity->RemoveComponent<FExternalComponent>();

        EXPECT_EQ(Entity->GetComponent<FExternalComponent>(), nullptr);
    }
}

TEST(SwarmTests, EntityComponentCreation)
{
    const char* TestContent = "Test Component";
    Swarm::Manager* Manager = Swarm::Manager::Get();

    std::shared_ptr<FTestEntity> Entity =
        Manager->MakeEntity<FTestEntity>(TestContent);

    Entity = nullptr;

    // Check that the component was also removed
    EXPECT_EQ(Manager->GetComponentCount<FContentComponent>(), 0);
}

class KTestSystem : public Swarm::KSystem
{
public:
    virtual void Initialize() override {}

    virtual void Execute(float DeltaTime) override
    {
        UNUSED_VAR(DeltaTime);

        for (FExternalComponent& Component :
             GetComponents<FExternalComponent>())
        {
            Component.Value += 1;
        }
    }

    virtual void Shutdown() override {}
};

TEST(SwarmTests, SystemExecution)
{
    Swarm::Manager* Manager = Swarm::Manager::Get();

    std::shared_ptr<FTestEntity> Entity =
        Manager->MakeEntity<FTestEntity>("Test Entity");

    std::shared_ptr<FTestEntity> AnotherEntity =
        Manager->MakeEntity<FTestEntity>("Another Test Entity");

    Entity->AddComponent<FExternalComponent>(0);
    AnotherEntity->AddComponent<FExternalComponent>(1);

    EXPECT_EQ(Entity->GetComponent<FExternalComponent>()->Value, 0);
    EXPECT_EQ(AnotherEntity->GetComponent<FExternalComponent>()->Value, 1);

    Manager->AddSystem<KTestSystem>();

    Manager->Update(0.0f);

    Manager->RemoveSystem<KTestSystem>();

    EXPECT_EQ(Entity->GetComponent<FExternalComponent>()->Value, 1);
    EXPECT_EQ(AnotherEntity->GetComponent<FExternalComponent>()->Value, 2);
}
