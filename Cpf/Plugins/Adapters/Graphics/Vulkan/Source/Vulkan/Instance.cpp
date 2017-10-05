//////////////////////////////////////////////////////////////////////////
#include "Vulkan/Instance.hpp"

using namespace CPF;
using namespace Vulkan;
using namespace Graphics;

Instance::Instance(iUnknown*)
	: mInstance(nullptr)
{}

Instance::~Instance()
{}

GOM::Result CPF_STDCALL Instance::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		*outIface = nullptr;
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iInstance*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Instance::Initialize(Plugin::iRegistry* registry)
{
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Instance::EnumerateAdapters(int* count, iAdapter** adapters)
{
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Instance::CreateDevice(iAdapter* adapter, iDevice** device)
{
	return GOM::kOK;
}
