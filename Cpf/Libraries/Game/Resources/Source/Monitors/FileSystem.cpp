//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/ID.hpp"
#include "Resources/iLocator.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

GOM::Result CPF_STDCALL FileSystem::Cast(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case iBase::kIID.GetID():
			*outIface = static_cast<iBase*>(this);
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

FileSystem::FileSystem(iBase*)
{}

FileSystem::~FileSystem()
{}
