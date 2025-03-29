#include "Core/CoreMinimal.h"

#include <cstdlib>

#include "SwarmEngine.h"

static KSwarmEngine* GEngine = nullptr;

int main()
{
    GEngine = new KSwarmEngine();

    // Initialize the engine
    {
        GEngine->Initialize();
    }

    while (GEngine->IsEngineExitRequired() == false)
    {
        GEngine->EngineTick(0.0f);
    }

    // Shutdown the engine
    {
        GEngine->Shutdown();
        delete GEngine;
        GEngine = nullptr;
    }

    return EXIT_SUCCESS;
}
