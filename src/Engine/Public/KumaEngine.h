#pragma once

class KKumaEngine
{
public:
    KKumaEngine();
    ~KKumaEngine();

    void Initialize();
    void Shutdown();

    void EngineTick(float DeltaTime);

    void RequireEngineExit();

    bool IsEngineExitRequired() const;

private:
    bool bExitRequired = false;
};
