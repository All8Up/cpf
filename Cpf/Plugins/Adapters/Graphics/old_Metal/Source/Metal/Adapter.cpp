//////////////////////////////////////////////////////////////////////////
#include "Adapters/Metal/Adapter.hpp"
#include "Adapters/Metal/SwapChain.hpp"
#include "IntrusivePtr.hpp"

using namespace Cpf;
using namespace Adapters;
using namespace Metal;

//////////////////////////////////////////////////////////////////////////
Adapter::~Adapter()
{
}

bool Adapter::IsSoftware()
{
	return false;
}
