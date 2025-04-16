#include "System.h"

namespace Swarm
{

void KSystem::Initialize() { bIsInitialized = true; }

void KSystem::Shutdown() { bIsInitialized = false; }

} // namespace Swarm
