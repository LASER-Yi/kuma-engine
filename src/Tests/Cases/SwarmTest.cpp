#include "Swarm/Definition.h"
#include "Swarm/Entity.h"
#include "Swarm/SwarmManager.h"
#include <gtest/gtest.h>

struct FTestEntity : public Swarm::FEntity
{
};

struct FTestComponent : public Swarm::IComponent
{
    static constexpr Swarm::ComponentType GetType() { return 82; }

    std::string Content;

    FTestComponent(const std::string& InContent) : Content(InContent) {}
};

TEST(SwarmTest, EntityCreation)
{
    // Create an entity
    Swarm::KManager* Manager = Swarm::KManager::Get();
    auto Entity = Manager->MakeEntity<FTestEntity>();

    // Check that the entity has a unique ID
    EXPECT_NE(Entity.GetUnderlyingIndex(), Swarm::Invalid);

    Manager->RemoveEntity(Entity);

    // Check that the entity has been removed
    EXPECT_EQ(Entity.GetUnderlyingIndex(), Swarm::Invalid);
}

TEST(SwarmTest, ComponentCreation)
{
    Swarm::KManager* Manager = Swarm::KManager::Get();

    auto Entity = Manager->MakeEntity<FTestEntity>();

    Manager->AddComponent<FTestComponent>(Entity, "FTestComponent");

    FTestComponent* Component = Manager->GetComponent<FTestComponent>(Entity);

    // Check that the component was added successfully
    EXPECT_NE(Component, nullptr);
}
