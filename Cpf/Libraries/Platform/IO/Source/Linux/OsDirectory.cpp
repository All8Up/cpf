//////////////////////////////////////////////////////////////////////////
#include "IO/Directory.hpp"
#include "IO/Path.hpp"


namespace Cpf
{
	namespace IO
	{
		void Directory::CurrentWorkingDirectory(const String& dir)
		{
			// TODO: Implement for OsX.
		}


		const String Directory::CurrentWorkingDirectory()
		{
			String result;
			// TODO: Implement for OsX.
			return result;
		}


		Directory::FileList Directory::Files(const String& dir)
		{
			// TODO: Implement for OsX.
			FileList result;
			return result;
		}


		Directory::FileList Directory::Files(const String& dir, const String& pattern)
		{
			// TODO: Implement for OsX.
			FileList result;
			return result;
		}
	}
}
