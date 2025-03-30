#include "Swarm/Manager.h"
#include "Swarm/Definition.h"

namespace Swarm
{

Manager::Manager() {}

Manager::~Manager() {}

void Manager::Update(float DeltaTime)
{
    // TODO: Refactor system update via multithreading

    for (const auto& System : Systems)
    {
        System->Update(DeltaTime);
    }
}

void Manager::RemoveEntity(FEntityBase* Entity)
{
    if (Entity == nullptr)
    {
        return;
    }

    if (EntityToComponents.contains(Entity->GetIndex()))
    {
        const auto& EntityComponents = EntityToComponents[Entity->GetIndex()];

        for (const auto& [InComponentType, InComponentIndex] : EntityComponents)
        {
            Components[InComponentType].Remove(InComponentIndex);
        }

        EntityToComponents.erase(Entity->GetIndex());
    }

    FreeEntityIndices.push(Entity->GetIndex());
}

Swarm::EntityIndex Manager::AllocateEntityIndex()
{
    Swarm::EntityIndex NewIndex = Swarm::InvalidIndex;
    if (FreeEntityIndices.empty() == false)
    {
        NewIndex = FreeEntityIndices.front();
        FreeEntityIndices.pop();
    }
    else
    {
        NewIndex = NextEntityIndex;
        ++NextEntityIndex;

        assert(
            NextEntityIndex < std::numeric_limits<Swarm::EntityIndex>::max()
        );
    }

    return NewIndex;
}

} // namespace Swarm
