#include "Core/CoreMinimal.h"
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

} // namespace Swarm
