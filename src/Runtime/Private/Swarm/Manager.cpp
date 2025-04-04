#include "Swarm/Manager.h"
#include "Swarm/Definition.h"

namespace Swarm
{

void Manager::Update(float DeltaTime)
{
    // TODO: Refactor system update via multithreading

    for (const auto& [SystemType, System] : Systems)
    {
        UNUSED_VAR(SystemType);

        System->Execute(DeltaTime);
    }
}

void Manager::Shutdown()
{
    // TODO[Multithread]: Wait for all systems to stop

    // Shutdown all systems
    {
        for (auto [SystemType, System] : Systems)
        {
            System->Shutdown();
        }
        Systems.clear();
    }

    // Remove all components
    {
        Components.Clear();
    }

    // Remove all entities
    {
        EntityToComponents.clear();
        EntitySignature.Reset();
    }
}

void Manager::RemoveEntity(FEntityBase* Entity)
{
    if (Entity == nullptr)
    {
        return;
    }

    const Swarm::SignatureType Signature = Entity->Signature;

    if (EntityToComponents.contains(Signature))
    {
        const auto& EntityComponents = EntityToComponents[Signature];

        for (const auto& [InComponentType, InComponentSignature] :
             EntityComponents)
        {
            Components.Remove(InComponentType, InComponentSignature);
        }

        EntityToComponents.erase(Signature);
    }

    Entity->Signature = Swarm::InvalidSignature;
    EntitySignature.Release(Signature);
}

} // namespace Swarm
