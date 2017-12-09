//////////////////////////////////////////////////////////////////////////
#include "IO/Directory.hpp"
#include "IO/File.hpp"
#include "IO/Path.hpp"

using namespace CPF;
using namespace IO;


CPF_EXPORT_IO bool Directory::Exists(const String& dir)
{
	return OsExists(dir);
}

CPF_EXPORT_IO bool Directory::Create(const String& dir, bool recursive)
{
	if (!recursive)
		return OsCreate(dir);
	else
	{
		auto components = Path::Components(dir);
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

CPF_EXPORT_IO bool Directory::Delete(const String& dir, bool recursive)
{
	if (!recursive)
		return OsDelete(dir);
	else
	{
		String current = dir;
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
