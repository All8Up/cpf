//////////////////////////////////////////////////////////////////////////
#include "Adapters/D3D12.hpp"
#include "Graphics/Factory.hpp"

#include "Adapters/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapters;

namespace
{
	int s_RefCount = 0;
}

CPF_EXPORT_ADAPTERS_D3D12 int D3D12Initializer::Install()
{
	if (++s_RefCount == 1)
	{
		CPF_INIT_LOG(D3D12);
		Graphics::Install(1, &D3D12::Instance::Create);
//		Graphics::Install(GetRtti<Graphics::Adapter::iSwapChain>(), &D3D12::SwapChain::Create);
	}
	return s_RefCount;
}

CPF_EXPORT_ADAPTERS_D3D12 int D3D12Initializer::Remove()
{
	if ((--s_RefCount) == 0)
	{
		Graphics::Remove(1);
		CPF_DROP_LOG(D3D12);
	}
	return s_RefCount;
}
