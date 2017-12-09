//////////////////////////////////////////////////////////////////////////
#include "SharedLibrary/SharedLibrary.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Platform;

SharedLibrary::SharedLibrary(const String& name)
	: mLibraryName(name)
	, mpLibrary(Load(name.c_str()))
{
}

SharedLibrary::SharedLibrary(SharedLibrary&& rhs)
	: mLibraryName(std::move(rhs.mLibraryName))
	, mpLibrary(rhs.mpLibrary)
{
	rhs.mpLibrary = nullptr;
}

SharedLibrary::~SharedLibrary()
{
	if (mpLibrary)
	{
		Unload(mpLibrary);
	}
}

SharedLibrary::operator bool() const
{
	return mpLibrary != nullptr;
}

void* SharedLibrary::Find(const String& name)
{
	if (mpLibrary)
	{
		CPF_LOG(SharedLibrary, Trace) << "Getting function " << name.c_str() << " from library: " << mLibraryName.c_str();
		return FindSymbol(mpLibrary, name.c_str());
	}
	return nullptr;
}
