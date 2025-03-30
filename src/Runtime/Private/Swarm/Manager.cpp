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

    const Swarm::SignatureType Signature = Entity->GetSignature();

    if (EntityToComponents.contains(Signature))
    {
        const auto& EntityComponents = EntityToComponents[Signature];

        for (const auto& [InComponentType, InComponentSignature] :
             EntityComponents)
        {
            UNUSED_VAR(InComponentType);
            UNUSED_VAR(InComponentSignature);
            // TODO: How to remove the component without knowing the type?
            // Components[InComponentType].Remove(InComponentIndex);
        }

        EntityToComponents.erase(Signature);
    }

    EntitySignature.Release(Signature);
}

} // namespace Swarm
