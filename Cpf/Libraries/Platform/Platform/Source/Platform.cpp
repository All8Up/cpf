//////////////////////////////////////////////////////////////////////////
#include "Cpf/Platform.hpp"
#include "Time/Time.hpp"

using namespace Cpf;
using namespace Platform;

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_PLATFORM bool PlatformInitializer::Install()
{
	if (TimeInitializer::Install() > 0)
		return true;
	return false;
}

CPF_EXPORT_PLATFORM bool PlatformInitializer::Remove()
{
	TimeInitializer::Remove();
	return true;
}
