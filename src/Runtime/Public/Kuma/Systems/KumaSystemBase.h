#pragma once

#include "Kuma/KumaEngine.h"
#include "System.h"

class KKumaSystemBase : public Swarm::KSystem
{

protected:
    KKumaEngine* GetEngine() const;
};
