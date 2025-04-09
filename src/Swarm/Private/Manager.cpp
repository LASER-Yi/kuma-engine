#include "Manager.h"
#include "Definition.h"
#include "SystemUpdateContext.h"

namespace Swarm
{

void Manager::Update(float DeltaTime)
{
    // TODO: Refactor system update via multithreading

    const FSystemUpdateContext Context = {
        .DeltaTime = DeltaTime, .Manager = this
    };

    for (const auto& [SystemType, System] : Systems)
    {
        System->Execute(Context);
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

void Manager::FilterEntityByComponents(
    std::vector<SignatureType>& OutEntities,
    const std::span<SignatureType>& InComponents
)
{
    // TODO: Optimize this
    for (const auto& [Entity, Components] : EntityToComponents)
    {
        bool bResult = true;
        for (const auto& Requirement : InComponents)
        {
            if (Components.contains(Requirement) == false)
            {
                bResult = false;
                break;
            }
        }

        if (bResult)
        {
            OutEntities.push_back(Entity);
        }
    }
}

} // namespace Swarm
