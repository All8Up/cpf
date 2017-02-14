//
#include "IO/File.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace Cpf;
using namespace Platform;
using namespace IO;

CPF_EXPORT_IO bool File::Exists(const String& name)
{
	struct stat data;
	if(stat(name.c_str(), &data)==0)
	{
		if( (data.st_mode & S_IFMT) == S_IFREG )
			return true;
	}
	return false;
}

CPF_EXPORT_IO bool File::Exists(const WString& name)
{
	String temp;
	for (auto c : name)
		temp.push_back(char(c));
	return Exists(String(temp));
}

CPF_EXPORT_IO bool File::Delete(const String& name)
{
	return ::unlink(name.c_str()) == 0;
}

CPF_EXPORT_IO bool File::Delete(const WString& name)
{
	String temp;
	for (auto c : name)
		temp.push_back(char(c));
	return ::unlink(temp.c_str()) == 0;
}
