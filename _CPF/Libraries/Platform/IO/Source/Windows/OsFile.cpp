//////////////////////////////////////////////////////////////////////////
#include "IO/File.hpp"

using namespace CPF;
using namespace IO;

CPF_EXPORT_IO bool File::Exists(const String& name)
{
	DWORD ftype = GetFileAttributesA(name.c_str());
	if (ftype == INVALID_FILE_ATTRIBUTES)
		return false;
	if ((ftype & FILE_ATTRIBUTE_DIRECTORY)==0)
		return true;
	return false;
}

CPF_EXPORT_IO bool File::Exists(const WString& name)
{
	DWORD ftype = GetFileAttributesW(name.c_str());
	if (ftype == INVALID_FILE_ATTRIBUTES)
		return false;
	if ((ftype & FILE_ATTRIBUTE_DIRECTORY) == 0)
		return true;
	return false;
}

CPF_EXPORT_IO bool File::Delete(const String& name)
{
	DWORD error = ::DeleteFileA(name.c_str());
	return error != 0;
}

CPF_EXPORT_IO bool File::Delete(const WString& name)
{
	return ::DeleteFileW(name.c_str()) != 0;
}
