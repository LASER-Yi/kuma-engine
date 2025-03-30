#include "Swarm/Manager.h"

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

    const auto& EntityComponents =
        EntityToComponents[Entity->GetUnderlyingIndex()];

    for (const auto& [InComponentType, InComponentIndex] : EntityComponents)
    {
        Components[InComponentType].Remove(InComponentIndex);
    }

    FreeEntityIndices.push(Entity->GetUnderlyingIndex());
}

} // namespace Swarm
