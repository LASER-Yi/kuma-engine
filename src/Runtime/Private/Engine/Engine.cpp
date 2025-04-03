#include "Engine/Engine.h"
#include "Renderer.h"

#include <memory>

#if PLATFORM_APPLE
#include "MetalRenderer.h"
#elif PLATFORM_WINDOWS
#include "D3D12Renderer.h"
#endif

extern void* GWindow;
KEngine* GEngine = nullptr;

KEngine::KEngine() : bExitRequired(false) {}

KEngine::~KEngine() {}

void KEngine::Initialize()
{
#if PLATFORM_APPLE
    Renderer = std::make_shared<KMetalRenderer>();
#elif PLATFORM_WINDOWS
    Renderer = std::make_shared<KD3D12Renderer>();
#endif

    Renderer->Initialize(GWindow);
    // TODO: initialize the swarm system
}

void KEngine::Shutdown()
{
    // TODO: Shutdown the swarm system
    Renderer->Shutdown();
}

void KEngine::EngineTick(float DeltaTime)
{
    Swarm::Manager::Get()->Update(DeltaTime);

    Renderer->Update();
}

void KEngine::RequireEngineExit() { bExitRequired = true; }

bool KEngine::IsEngineExitRequired() const { return bExitRequired; }

std::shared_ptr<IRenderer> KEngine::GetRenderer() const { return Renderer; }
