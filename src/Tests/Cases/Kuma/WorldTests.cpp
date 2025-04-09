#include "CoreMinimal.h"
#include "Kuma/Components/WorldEntity.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include "Manager.h"
#include <gtest/gtest.h>
#include <memory>

struct FKumaContentComponent : public Swarm::FComponent
{
    int Content;

    FKumaContentComponent(int InContent) : Content(InContent) {}
};

struct FKumaTestEntity : public FKumaEntity
{
    FKumaTestEntity(Swarm::FEntityInitializationContext& Context, int InContent)
        : FKumaEntity(Context)
    {
        Context.CreateDefaultComponent<FKumaContentComponent>(InContent);
    }
};

TEST(KumaWorldTests, WorldCreation)
{
    // Create an entity
    Swarm::Manager* Manager = Swarm::Manager::Get();
    std::shared_ptr<FKumaWorld> World = Manager->MakeEntity<FKumaWorld>();

    ASSERT_NE(World, nullptr);

    ASSERT_NE(World->GetComponent<FWorldEntityComponent>(), nullptr);

    World = nullptr;

    ASSERT_EQ(Manager->GetComponentCount<FWorldEntityComponent>(), 0);
}

TEST(KumaWorldTests, WorldEntityCreation)
{
    Swarm::Manager* Manager = Swarm::Manager::Get();
    auto World = Manager->MakeEntity<FKumaWorld>();

    const int TestContent = 114514;
    auto Entity = Manager->MakeEntity<FKumaTestEntity>(TestContent);

    World->AddToWorld(Entity);

    ASSERT_EQ(World.use_count(), 1);
    ASSERT_EQ(Entity.use_count(), 2);

    // Release the reference to the world entity
    Entity = nullptr;

    // The world should still holds the reference
    ASSERT_EQ(Manager->GetComponentCount<FKumaContentComponent>(), 1);

    World = nullptr;

    // World and all of its entities should be destroyed
    ASSERT_EQ(Manager->GetComponentCount<FWorldEntityComponent>(), 0);
    ASSERT_EQ(Manager->GetComponentCount<FKumaContentComponent>(), 0);
}
