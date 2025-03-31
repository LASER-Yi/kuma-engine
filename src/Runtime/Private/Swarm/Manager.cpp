#include "Swarm/Manager.h"
#include "Swarm/Definition.h"

namespace Swarm
{

Manager::Manager() {}

Manager::~Manager() {}

void Manager::Update(float DeltaTime)
{
    // TODO: Refactor system update via multithreading

    for (const auto& [SystemType, System] : Systems)
    {
        UNUSED_VAR(SystemType);

        System->Update(DeltaTime);
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

    EntitySignature.Release(Signature);
}

} // namespace Swarm
