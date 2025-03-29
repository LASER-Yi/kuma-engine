#include "CoreMinimal.h"

#include <cstdlib>

#include "Engine/Engine.h"

static KEngine* GEngine = nullptr;

int main()
{
    GEngine = new KEngine();

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
