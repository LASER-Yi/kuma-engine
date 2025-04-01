#include "Engine/Engine.h"

#include <memory>

#if PLATFORM_APPLE
#include "MetalRenderer.h"
#endif

extern void* GWindow;

KEngine::KEngine() : bExitRequired(false) {}

KEngine::~KEngine() {}

void KEngine::Initialize()
{
#if PLATFORM_APPLE
    Renderer = std::make_shared<KMetalRenderer>();
#endif

    Renderer->Initialize(GWindow);
}

void KEngine::Shutdown() { Renderer->Shutdown(); }

void KEngine::EngineTick(float DeltaTime)
{
    Swarm::Manager::Get()->Update(DeltaTime);

    Renderer->Update();
}

void KEngine::RequireEngineExit() { bExitRequired = true; }

bool KEngine::IsEngineExitRequired() const { return bExitRequired; }
