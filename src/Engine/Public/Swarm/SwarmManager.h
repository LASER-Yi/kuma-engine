#include "Core/CoreMinimal.h"
#include "Swarm/SwarmDefine.h"

#include <map>
#include <vector>
#include <memory>

#include "Swarm/Interfaces/System.h"
#include "Swarm/Entity.h"


namespace Swarm
{

struct FComponentArray
{
public:
};

class Manager final
{
public:
    Manager();
    ~Manager();

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Update(float DeltaTime);

private:
    std::vector<FEntity> Entities;
    std::map<Swarm::ComponentType, FComponentArray> Components;
    std::vector<std::shared_ptr<ISystem>> Systems;
};

}
