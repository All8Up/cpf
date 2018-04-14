//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/File.hpp"

using namespace CPF;
using namespace STD;
using namespace IO;

CPF_EXPORT bool File::Exists(const Utf8String& name)
{
	WString utf16;
	const auto validUtf8 = ConvertUtf8To16(name, utf16);
	if (validUtf8)
	{
		DWORD ftype = GetFileAttributesW(utf16.data());
		if (ftype == INVALID_FILE_ATTRIBUTES)
			return false;
		if ((ftype & FILE_ATTRIBUTE_DIRECTORY) == 0)
			return true;
	}
	return false;
}

CPF_EXPORT bool File::Delete(const Utf8String& name)
{
	WString utf16;
	const auto validUtf8 = ConvertUtf8To16(name, utf16);
	if (validUtf8)
		return ::DeleteFileW(utf16.c_str()) != 0;
	return false;
}
