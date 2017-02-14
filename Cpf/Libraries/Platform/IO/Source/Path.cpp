//
#include "IO/Path.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			namespace Path
			{
				template<> const char PathConstants<char>::kReversedSeparator = '\\';
				template<> const char PathConstants<char>::kDirectorySeparator = '/';
				template<> const char PathConstants<char>::kExtensionSeparator = '.';

				template<> const wchar_t PathConstants<wchar_t>::kReversedSeparator = L'\\';
				template<> const wchar_t PathConstants<wchar_t>::kDirectorySeparator = L'/';
				template<> const wchar_t PathConstants<wchar_t>::kExtensionSeparator = L'.';

#if CPF_TARGET_WINDOWS
				template<> const char PathConstants<char>::kOsDirectorySeparator = '\\';
				template<> const wchar_t PathConstants<wchar_t>::kOsDirectorySeparator = L'\\';
#elif CPF_TARGET_DARWIN
				template<> const char PathConstants<char>::kOsDirectorySeparator = '/';
				template<> const wchar_t PathConstants<wchar_t>::kOsDirectorySeparator = L'/';
#endif
			}
		}
	}
}
