#pragma once
#include "ExecutionContext.h"

class KKumaEngine;

namespace Swarm
{

/**
 * @brief Base class for all systems in the swarm.
 * @details This class defines the basic structure for all systems in the
 * swarm. Each system should implement the Initialize, Update, and Shutdown
 * methods.
 */
class KSystem
{
public:
    virtual void Initialize();

    virtual void Execute(const FExecutionContext& Context) = 0;

    virtual void Shutdown();

public:
    KSystem() = default;
    virtual ~KSystem() {}

    KSystem(const KSystem&) = delete;
    KSystem& operator=(const KSystem&) = delete;
    KSystem(KSystem&&) = delete;
    KSystem& operator=(KSystem&&) = delete;

private:
    bool bIsInitialized = false;
};

} // namespace Swarm
