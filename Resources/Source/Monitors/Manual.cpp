//////////////////////////////////////////////////////////////////////////
#include "Resources/Monitors/Manual.hpp"
#include "Resources/Locator.hpp"
#include "Resources/ID.hpp"

using namespace Cpf;
using namespace Resources;
using namespace Monitors;

CPF_EXPORT_RESOURCES Monitor* Manual::Create()
{
	return new Manual();
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

Manual::Manual()
{}

Manual::~Manual()
{}
