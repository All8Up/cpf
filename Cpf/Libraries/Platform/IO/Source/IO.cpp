//
#include "IO/IO.hpp"
#include "IO/FileSystem.hpp"

using namespace Cpf;
using namespace IO;

//////////////////////////////////////////////////////////////////////////
namespace
{
	int s_RefCount = 0;
	iFileSystem* s_pFileSystem = nullptr;
}

namespace Cpf
{
	namespace IO
	{
		extern CPF_EXPORT_IO iFileSystem* CreateFileSystem();
		extern CPF_EXPORT_IO void DestroyFileSystem(iFileSystem*);
	}
}


CPF_EXPORT_IO int IOInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
		SetFileSystem(CreateFileSystem());
	}
	return ++s_RefCount;
}

CPF_EXPORT_IO int IOInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		DestroyFileSystem(GetFileSystem());
		SetFileSystem(nullptr);
	}
	return s_RefCount;
}
