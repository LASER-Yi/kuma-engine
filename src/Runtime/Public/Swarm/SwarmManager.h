#pragma once

#include "CoreMinimal.h"
#include "Swarm/Interfaces/Component.h"
#include "Swarm/SwarmDefine.h"

#include <cassert>
#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "Swarm/Entity.h"
#include "Swarm/Interfaces/System.h"

namespace Swarm
{

struct FComponentArray
{
    FComponentArray() = delete;

    template <typename T>
    FComponentArray() : ContainerType(T::GetType()), ComponentSize(sizeof(T))
    {
        static_assert(
            std::is_base_of<IComponent, T>::value,
            "T must be derived from IComponent"
        );
    }

    void Remove(Swarm::ComponentIndex);

private:
    Swarm::ComponentType ContainerType;
    std::int32_t ComponentSize;
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

        if (FreeEntityIndices.empty() == false)
        {
            Swarm::EntityIndex NextIndex = FreeEntityIndices.front();
            T Entity(NextIndex);
            FreeEntityIndices.pop();

            return Entity;
        }
        else
        {
            T Entity(NextEntityIndex);
            ++NextEntityIndex;

            assert(
                NextEntityIndex < std::numeric_limits<Swarm::EntityIndex>::max()
            );

            return Entity;
        }
    }

    void RemoveEntity(FEntity& Entity);

private:
    std::map<Swarm::EntityIndex, std::vector<Swarm::FEntityComponent>>
        EntityToComponents;
    std::map<Swarm::ComponentType, FComponentArray> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;

private:
    Swarm::EntityIndex NextEntityIndex = 0;
    std::queue<Swarm::EntityIndex> FreeEntityIndices;
};

} // namespace Swarm
