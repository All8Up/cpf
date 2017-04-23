//////////////////////////////////////////////////////////////////////////
#include "Adapters/Metal/CommandBuffer.hpp"
#include "Adapters/Metal/CommandPool.hpp"
#include "Adapters/Metal/Device.hpp"
#include "Adapters/Metal/SwapChain.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Metal;

CommandBuffer::CommandBuffer(Graphics::Driver::iDevice* device, Graphics::Driver::iCommandPool* pool)
{
	Device* vulkanDevice = static_cast<Device*>(device);
	CommandPool* vulkanPool = static_cast<CommandPool*>(pool);
}

CommandBuffer::~CommandBuffer()
{}

void CommandBuffer::Begin()
{
}

void CommandBuffer::End()
{}

void CommandBuffer::Reset(Graphics::Driver::iCommandPool* pool)
{
}


void CommandBuffer::ToBePorted(Graphics::Driver::iDevice* device, Graphics::Driver::iSwapChain* swapChain)
{
}
