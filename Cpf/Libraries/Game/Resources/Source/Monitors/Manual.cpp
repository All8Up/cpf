//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/Manual.hpp"
#include "Resources/Locator.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

COM::Result CPF_STDCALL Manual::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case iUnknown::kIID.GetID():
			*outIface = static_cast<iUnknown*>(this);
			break;
		case iMonitor::kIID.GetID():
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


bool Manual::Touch(ID id)
{
	if (GetLocator())
		return GetLocator()->Touch(id);
	return false;
}

void Manual::TouchAll()
{
	if (GetLocator())
		GetLocator()->TouchAll();
}

Manual::Manual(iUnknown*)
{}

Manual::~Manual()
{}
