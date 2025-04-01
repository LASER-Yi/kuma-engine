#pragma once

class IRenderer
{
public:
    virtual void Initialize(void* WindowPtr) = 0;

    virtual void Update() = 0;

    virtual void Shutdown() = 0;
};
