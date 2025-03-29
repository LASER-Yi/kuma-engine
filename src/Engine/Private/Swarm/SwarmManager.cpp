#include "Core/CoreMinimal.h"

#include "Swarm/SwarmManager.h"

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

} // namespace Swarm
