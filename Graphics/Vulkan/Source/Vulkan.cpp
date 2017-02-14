//////////////////////////////////////////////////////////////////////////
#include "Adapters/Vulkan.hpp"
#include "Graphics/Factory.hpp"

#include "Adapters/Vulkan/Instance.hpp"

using namespace Cpf;
using namespace Adapters;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_ADAPTERS_VULKAN int VulkanInitializer::Install()
{
	if (++s_RefCount == 1)
	{
		Graphics::Install(2, &Vulkan::Instance::Create);
//		Graphics::Install(GetRtti<Graphics::Adapter::iSwapChain>(), &D3D12::SwapChain::Create);
	}
	return s_RefCount;
}

CPF_EXPORT_ADAPTERS_VULKAN int VulkanInitializer::Remove()
{
	if ((--s_RefCount) == 0)
	{
		Graphics::Remove(2);
	}
	return s_RefCount;
}
