#include "MetalCmdQueue.h"
#include "Metal/MTLCommandBuffer.hpp"
#include "MetalDevice.h"

#include <Metal/MTLCommandQueue.hpp>
#include <Metal/MTLDevice.hpp>

KMetalCmdQueue::KMetalCmdQueue(std::shared_ptr<KMetalDevice> InDevice)
{
    MetalCommandQueue = InDevice->Get()->newCommandQueue();
}

KMetalCmdQueue::~KMetalCmdQueue() { MetalCommandQueue->release(); }

MTL::CommandBuffer* KMetalCmdQueue::GetCmdBuffer()
{
    return MetalCommandQueue->commandBuffer();
}
