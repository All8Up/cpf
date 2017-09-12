#include "IO/Globbing.hpp"

using namespace CPF;
using namespace IO;

/**
 * @brief Provides a globbing algorithm to search for patterns in strings.
 * @param pattern  Specifies the pattern.
 * @param inString The string to match against.
 * @return true if the string contains the pattern, false otherwise.
 */
CPF_EXPORT_IO bool IO::Glob(const char *pattern, const char *inString)
{
	const char *current = nullptr;
	const char *mp = nullptr;

	while ((*inString) && (*pattern != '*'))
	{
		if ((*pattern != *inString) && (*pattern != '?'))
			return false;
		pattern++;
		inString++;
	}

	while (*inString)
	{
		if (*pattern == '*')
		{
			if (!*++pattern)
				return true;
			mp = pattern;
			current = inString + 1;
		}
		else if ((*pattern == *inString) || (*pattern == '?'))
		{
			pattern++;
			inString++;
		}
		else
		{
			pattern = mp;
			inString = current++;
		}
	}

	while (*pattern == '*')
		pattern++;
	return (!*pattern) != 0;
}


/**
* @brief Provides a globbing algorithm to search for patterns in strings.
* @param pattern  Specifies the pattern.
* @param inString The string to match against.
* @return true if the string contains the pattern, false otherwise.
*/
CPF_EXPORT_IO bool IO::Glob(const wchar_t *pattern, const wchar_t *inString)
{
	const wchar_t *current = nullptr;
	const wchar_t *mp = nullptr;

	while ((*inString) && (*pattern != L'*'))
	{
		if ((*pattern != *inString) && (*pattern != L'?'))
			return false;
		pattern++;
		inString++;
	}

	while (*inString)
	{
		if (*pattern == L'*')
		{
			if (!*++pattern)
				return true;
			mp = pattern;
			current = inString + 1;
		}
		else if ((*pattern == *inString) || (*pattern == L'?'))
		{
			pattern++;
			inString++;
		}
		else
		{
			pattern = mp;
			inString = current++;
		}
	}

	while (*pattern == L'*')
		pattern++;
	return (!*pattern) != 0;
}
