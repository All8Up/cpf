//////////////////////////////////////////////////////////////////////////
#include "Adapters/Vulkan/Adapter.hpp"
#include "Adapters/Vulkan/SwapChain.hpp"
#include "IntrusivePtr.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Vulkan;

//////////////////////////////////////////////////////////////////////////
Adapter::~Adapter()
{
}

bool Adapter::IsSoftware()
{
	return false;
}
