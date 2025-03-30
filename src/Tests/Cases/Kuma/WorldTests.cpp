#include "CoreMinimal.h"
#include "Kuma/Components/WorldEntity.h"
#include "Kuma/Entities/KumaEntity.h"
#include "Kuma/Entities/KumaWorld.h"
#include <gtest/gtest.h>
#include <memory>

struct FContentComponent : public Swarm::IComponent<FContentComponent>
{
    int Content;

    FContentComponent(int InContent) : Content(InContent) {}
};

struct FTestEntity : public FKumaEntity
{
    FTestEntity(int InContent) : FKumaEntity()
    {
        AddComponent<FContentComponent>(InContent);
    }
};

TEST(KumaWorldTests, WorldCreation)
{
    // Create an entity
    Swarm::Manager* Manager = Swarm::Manager::Get();
    std::shared_ptr<FKumaWorld> World = Manager->MakeEntity<FKumaWorld>();

    ASSERT_NE(World, nullptr);

    ASSERT_NE(World->GetComponent<FWorldEntityComponent>(), nullptr);
}
