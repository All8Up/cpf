//////////////////////////////////////////////////////////////////////////
#include "Rtti.hpp"
#include "Adapters/Metal.hpp"
#include "Graphics/Factory.hpp"

#include "Adapters/Metal/Instance.hpp"

using namespace Cpf;
using namespace Adapters;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_ADAPTERS_METAL int MetalInitializer::Install()
{
	if (++s_RefCount == 1)
	{
		Graphics::Install(GetRtti<Graphics::Driver::iInstance>(), &Metal::Instance::Create);
//		Graphics::Install(GetRtti<Graphics::Adapter::iSwapChain>(), &D3D12::SwapChain::Create);
	}
	return s_RefCount;
}

CPF_EXPORT_ADAPTERS_METAL int MetalInitializer::Remove()
{
	if ((--s_RefCount) == 0)
	{
		Graphics::Remove(GetRtti<Metal::Instance>());
	}
	return s_RefCount;
}
