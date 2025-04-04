#include "Engine/Engine.h"
#include "Renderer.h"
#include "Swarm/Manager.h"

#include <memory>

#if PLATFORM_APPLE
#include "MetalRenderer.h"
#elif PLATFORM_WINDOWS
#include "D3D12Renderer.h"
#endif

KEngine* GEngine = nullptr;

KEngine::KEngine() : bExitRequired(false) {}

KEngine::~KEngine() {}

void KEngine::SetWindow(void* Handle) { WindowHandle = Handle; }

void KEngine::Initialize()
{
#if PLATFORM_APPLE
    Renderer = std::make_shared<KMetalRenderer>();
#elif PLATFORM_WINDOWS
    Renderer = std::make_shared<KD3D12Renderer>();
#endif

    Renderer->Initialize(WindowHandle);
}

void KEngine::Update()
{
    Swarm::Manager::Get()->Update(0.0f);

    Renderer->Update();
}

void KEngine::Shutdown()
{
    Swarm::Manager::Get()->Shutdown();
    Renderer->Shutdown();
}

void KEngine::RequireEngineExit() { bExitRequired = true; }

bool KEngine::IsEngineExitRequired() const { return bExitRequired; }

std::shared_ptr<KRenderer> KEngine::GetRenderer() const { return Renderer; }
