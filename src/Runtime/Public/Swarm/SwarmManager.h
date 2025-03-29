#pragma once

#include "CoreMinimal.h"
#include "Swarm/SwarmDefine.h"

#include <map>
#include <memory>
#include <vector>

#include "Swarm/Entity.h"
#include "Swarm/Interfaces/System.h"

namespace Swarm
{

struct FComponentArray
{
    void Remove(Swarm::ComponentIndex);

private:
};

struct FEntityComponent
{
    Swarm::ComponentType Type = Swarm::Invalid;
    Swarm::ComponentIndex Index = Swarm::Invalid;
};

class Manager final
{
public:
    Manager();
    ~Manager();

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Update(float DeltaTime);

    template <typename T>
    T MakeEntity()
    {
        static_assert(
            std::is_base_of<FEntity, T>::value, "T must be derived from FEntity"
        );

        static_assert(
            sizeof(T) == sizeof(FEntity), "T must be the same size as FEntity"
        );

        T Entity(NextEntityIndex);
        ++NextEntityIndex;
        return Entity;
    }

    void RemoveEntity(FEntity& Entity);

private:
    std::map<Swarm::EntityIndex, std::vector<Swarm::FEntityComponent>>
        EntityToComponents;
    std::map<Swarm::ComponentType, FComponentArray> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;

private:
    Swarm::EntityIndex NextEntityIndex = 0;
};

} // namespace Swarm
