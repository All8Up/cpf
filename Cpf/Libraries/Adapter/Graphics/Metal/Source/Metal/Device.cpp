//////////////////////////////////////////////////////////////////////////
#include "Adapters/Metal/Device.hpp"
#include "Adapters/Metal/Adapter.hpp"
#include "Adapters/Metal/Instance.hpp"
#include "Adapters/Metal/CommandPool.hpp"
#include "Adapters/Metal/CommandBuffer.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Metal;

CPF_DEFINE_RTTI(Device);


Device::Device(Graphics::Driver::iAdapter* adapter)
{
}

Device::~Device()
{}


bool Device::CreateCommandPool(Graphics::Driver::iCommandPool** pool)
{
	CommandPool* result = new CommandPool(this);
	if (pool)
	{
		*pool = result;
		return true;
	}
	return false;
}

bool Device::CreateCommandBuffer(Graphics::Driver::iCommandPool* pool, Graphics::Driver::iCommandBuffer** buffer)
{
	CommandBuffer* result = new CommandBuffer(this, pool);
	if (result)
	{
		*buffer = result;
		return true;
	}
	return false;
}
