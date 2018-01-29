//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/Directory.hpp"
#include "CPF/IO/File.hpp"
#include "CPF/IO/Path.hpp"

using namespace CPF;
using namespace IO;


CPF_EXPORT bool Directory::Exists(const Std::Utf8String& dir)
{
	return OsExists(dir);
}

CPF_EXPORT bool Directory::Create(const Std::Utf8String& dir, bool recursive)
{
	if (!recursive)
		return OsCreate(dir);
	else
	{
		// TODO: Temporary direct utf8 to string conversion.
		auto components = Path::Components(dir.data());
		String current;
		for (const auto& component : components)
		{
			current = Path::Combine(current, component);
			if (Exists(current))
				continue;

			if (!OsCreate(current))
				return false;
		}
	}

	return true;
}

CPF_EXPORT bool Directory::Delete(const Std::Utf8String& dir, bool recursive)
{
	if (!recursive)
		return OsDelete(dir);
	else
	{
		// TODO: Temporary direct utf8 to string conversion.
		String current = dir.data();
		for (const auto& it : Directories(dir))
		{
			// Ignore the links . and ..
			if (it.mName == "." || it.mName == "..")
				continue;

			// Delete child paths.
			if (!Delete(Path::Combine(current, it.mName), true))
				return false;
		}

		// Now delete the contents which are not directories.
		for (const auto& it : Entries(dir))
		{
			if (IsSet(it.mAttributes, Attributes::eFile))
			{
				if (!File::Delete(Path::ToOS(Path::Combine(current, it.mName))))
					return false;
			}
		}

		// Now delete ourselves.
		return OsDelete(current);
	}
}
