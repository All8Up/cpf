//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/FileSystem.hpp"

using namespace CPF;
using namespace IO;

namespace CPF
{
	namespace IO
	{
		iFileSystem* CreateFileSystem();
	}
}

namespace
{
	iFileSystem* s_pFileSystem = nullptr;
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT iFileSystem* IO::GetFileSystem()
{
	if (s_pFileSystem == nullptr)
		s_pFileSystem = CreateFileSystem();
	return s_pFileSystem;
}

CPF_EXPORT void IO::SetFileSystem(iFileSystem* fs)
{
	s_pFileSystem = fs;
}


//////////////////////////////////////////////////////////////////////////
iFileSystem::~iFileSystem()
{}
