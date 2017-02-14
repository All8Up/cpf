//
#include "IO/File.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



namespace Cpf
{
	namespace IO
	{
		bool File::Exists(const String& name)
		{
			struct stat data;
			if(stat(name.c_str(), &data)==0)
			{
				if( (data.st_mode & S_IFMT) == S_IFREG )
					return true;
			}
			return false;
		}

		bool File::Exists(const WString& name)
		{
			String temp;
			for (auto c : name)
				temp.push_back(char(c));
			return Exists(String(temp));
		}
	}
}
