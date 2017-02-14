//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12.hpp"
#include "Graphics.hpp"

#include "Adapter/D3D12/Instance.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Adapter;

namespace
{
	int s_RefCount = 0;
}


// TODO: This is just a temporary factory to get things running.
CPF_EXPORT_ADAPTER_D3D12 bool Cpf::Graphics::Create(int64_t id, Graphics::iInstance** instance)
{
	*instance = reinterpret_cast<Graphics::iInstance*>(D3D12::Instance::Create());
	return true;
}

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Install()
{
	if (++s_RefCount == 1)
	{
		CPF_INIT_LOG(D3D12);
	}
	return s_RefCount;
}

CPF_EXPORT_ADAPTER_D3D12 int D3D12Initializer::Remove()
{
	if ((--s_RefCount) == 0)
	{
		CPF_DROP_LOG(D3D12);
	}
	return s_RefCount;
}
