#include "Kuma/Systems/KumaSystemBase.h"
#include "Engine/Engine.h"
#include "Kuma/KumaEngine.h"

extern KEngine* GEngine;

KKumaEngine* KKumaSystemBase::GetEngine() const
{
    return static_cast<KKumaEngine*>(GEngine);
}
