#include "Engine/Engine.h"
#include "Renderer.h"
#include "Swarm/Manager.h"

#include <chrono>
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

    LastTickWorldTimeSeconds = GetWorldTimeSeconds();
}

void KEngine::Update()
{
    const double CurrentTimeSeconds = GetWorldTimeSeconds();
    const float DeltaTime =
        static_cast<float>(CurrentTimeSeconds - LastTickWorldTimeSeconds);
    LastTickWorldTimeSeconds = CurrentTimeSeconds;

    Swarm::Manager::Get()->Update(DeltaTime);

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

double KEngine::GetWorldTimeSeconds() const
{
    using namespace std::chrono;
    const auto now = steady_clock::now().time_since_epoch();
    return duration_cast<microseconds>(now).count() / 1000000.0;
}
