#include "CoreMinimal.h"

#include <cstdlib>
#include <iostream>
#include <shared_mutex>

#include "Kuma/KumaEngine.h"

extern KEngine* GEngine;

void* GWindow = nullptr;

std::shared_mutex EngineExitLock;

void RequestEngineExit()
{
    std::unique_lock<std::shared_mutex> Lock(EngineExitLock);
    if (GEngine)
    {
        GEngine->RequireEngineExit();
    }
}

bool IsEngineExitRequested()
{
    std::shared_lock<std::shared_mutex> Lock(EngineExitLock);
    if (GEngine)
    {
        return GEngine->IsEngineExitRequired();
    }
    return true;
}

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
