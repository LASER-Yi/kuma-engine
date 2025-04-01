#pragma once

#include <memory>

namespace MTL
{
class CommandBuffer;
class CommandQueue;
} // namespace MTL

class KMetalDevice;

class KMetalCmdQueue
{
public:
    KMetalCmdQueue(std::shared_ptr<KMetalDevice> InDevice);

    ~KMetalCmdQueue();

    MTL::CommandBuffer* AllocCmd();

private:
    MTL::CommandQueue* MetalCommandQueue;
};
