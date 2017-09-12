//////////////////////////////////////////////////////////////////////////
#include "IO/FileSystem.hpp"

using namespace CPF;
using namespace IO;

namespace
{
	iFileSystem* s_pFileSystem = nullptr;
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_IO iFileSystem* IO::GetFileSystem()
{
	return s_pFileSystem;
}

CPF_EXPORT_IO void IO::SetFileSystem(iFileSystem* fs)
{
	s_pFileSystem = fs;
}


//////////////////////////////////////////////////////////////////////////
iFileSystem::~iFileSystem()
{}
