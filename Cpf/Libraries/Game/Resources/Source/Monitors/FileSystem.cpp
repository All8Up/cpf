//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/FileSystem.hpp"
#include "Resources/ID.hpp"
#include "Resources/iLocator.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

COM::Result CPF_STDCALL FileSystem::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case kIID.GetID():
			*outIface = static_cast<iMonitor*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool FileSystem::Touch(ID id)
{
	(void)id;
	return false;
}

void FileSystem::TouchAll()
{}

FileSystem::FileSystem(iUnknown*)
{}

FileSystem::~FileSystem()
{}
