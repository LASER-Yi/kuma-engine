#include "Swarm/System.h"
#include "Kuma/KumaEngine.h"

// TODO: Find a better way to declare global symbol
extern KEngine* GEngine;

namespace Swarm
{

KKumaEngine* KSystem::GetEngine() const
{
    return static_cast<KKumaEngine*>(GEngine);
}

} // namespace Swarm
