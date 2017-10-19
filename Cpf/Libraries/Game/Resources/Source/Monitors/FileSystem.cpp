//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/ID.hpp"
#include "Resources/iLocator.hpp"

using namespace CPF;
using namespace Resources;
using namespace Monitors;

GOM::Result CPF_STDCALL FileSystem::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iMonitor*>(this);
			break;
		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

bool FileSystem::Touch(ID id)
{
	(void)id;
	return false;
}

void FileSystem::TouchAll()
{}

FileSystem::FileSystem(Plugin::iRegistry*, iUnknown*)
{}

FileSystem::~FileSystem()
{}
