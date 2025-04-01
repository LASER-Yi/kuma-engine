#include "CoreMinimal.h"

#include <cstdlib>
#include <iostream>

#include "Kuma/KumaEngine.h"

static KEngine* GEngine = nullptr;

int GuardedMain(const char* CmdLine)
{
    // TODO: Better logging support
    std::cout << "Starting KumaEngine..." << std::endl;

    if (CmdLine != nullptr)
    {
        std::cout << "Command line: " << CmdLine << std::endl;
    }

    GEngine = new KKumaEngine();

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
