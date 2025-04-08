#include "CoreMinimal.h"

#include <cstdlib>
#include <iostream>

#include "Engine/Engine.h"
#include "Kuma/KumaEngine.h"

extern KEngine* GEngine;

void* WindowHandle = nullptr;

void RequestEngineExit()
{
    if (GEngine)
    {
        GEngine->RequireEngineExit();
    }
}

bool IsEngineExitRequested()
{
    if (GEngine)
    {
        return GEngine->IsEngineExitRequired();
    }
    return true;
}

void EngineSetWindow(void* Handle) { WindowHandle = Handle; }

void EngineInitialize(const char* CmdLine)
{
    // TODO: Better logging support
    std::cout << "Starting KumaEngine..." << std::endl;

    if (CmdLine != nullptr)
    {
        std::cout << "Command line: " << CmdLine << std::endl;
    }

    GEngine = new KKumaEngine();

    FEngineInitializationContext InitializationContext{
        .CmdLine = CmdLine, .WindowHandle = WindowHandle
    };

    // Initialize the engine
    {
        GEngine->Initialize(InitializationContext);
    }
}

bool EngineLoop()
{
    if (GEngine->IsEngineExitRequired())
    {
        return false;
    }

    GEngine->Update();
    return true;
}

int EngineShutdown()
{
    // Shutdown the engine
    GEngine->Shutdown();
    delete GEngine;
    GEngine = nullptr;

    return EXIT_SUCCESS;
}
