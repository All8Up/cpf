//////////////////////////////////////////////////////////////////////////
#include "IO/Directory.hpp"
#include "IO/Path.hpp"
#include "Move.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>


using namespace Cpf;
using namespace Platform;
using namespace IO;


void Directory::SetWorkingDirectory(const String &dir)
{
	chdir(dir.c_str());
}


String Directory::GetWorkingDirectory()
{
	char buffer[FILENAME_MAX];
	getcwd(buffer, FILENAME_MAX);
	return String(buffer);
}


bool Directory::OsExists(const String& dir)
{
	struct stat status;
	if (stat(dir.c_str(), &status)==0)
	{
		if ((status.st_mode & S_IFDIR) != 0)
			return true;
	}
	return false;
}

bool Directory::OsCreate(const String& dir)
{
	return mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

bool Directory::OsDelete(const String& dir)
{
	return rmdir(dir.c_str()) == 0;
}


//////////////////////////////////////////////////////////////////////////
struct Directory::Entries::OsIterator
{
	OsIterator()
		: mpDir(nullptr)
		, mpEntry(nullptr)
	{}

	~OsIterator()
	{
		if (mpDir)
			::closedir(mpDir);
	}

	DIR* mpDir;
	struct dirent* mpEntry;
	Predicate mPredicate;

	bool Init(const String& path, Predicate&& pred)
	{
		String searchPath = Path::ToOS(Path::Normalize(path));
		mPredicate = Move(pred);

		mpDir = opendir(searchPath.c_str());
		if (mpDir != nullptr && Next())
			return true;
		return false;
	}

	bool Next()
	{
		bool more = true;
		do
		{
			mpEntry = ::readdir(mpDir);
			more = mpEntry != nullptr;
		} while (more && !mPredicate(ToEntry()));
		return more;
	}

	DirEntry ToEntry()
	{
		DirEntry result;
		result.mName = mpEntry->d_name;
		result.mAttributes = 0;
		if ((mpEntry->d_type&DT_REG)==DT_REG)
			result.mAttributes |= eFile;
		if ((mpEntry->d_type&DT_DIR)==DT_DIR)
			result.mAttributes |= eDirectory;
		if ((mpEntry->d_type&DT_LNK)==DT_LNK)
			result.mAttributes |= eSymlink;

		return result;
	}
};



//////////////////////////////////////////////////////////////////////////
Directory::Entries::Iterator::Iterator()
	: mpIterator(nullptr)
{
}

Directory::Entries::Iterator::Iterator(const String& path, Predicate&& pred)
	: mpIterator(new OsIterator)
{
	if (mpIterator)
	{
		if (!mpIterator->Init(path, Move(pred)))
		{
			delete mpIterator;
			mpIterator = nullptr;
		}
	}
}


Directory::Entries::Iterator::Iterator(Iterator&& rhs) noexcept
	: mpIterator(rhs.mpIterator)
{
	rhs.mpIterator = nullptr;
}


Directory::Entries::Iterator::~Iterator()
{
	delete mpIterator;
}

bool Directory::Entries::Iterator::operator !=(const Iterator& rhs) const
{
	if (mpIterator == nullptr || rhs.mpIterator == nullptr)
		return mpIterator != rhs.mpIterator;
	return false;
}

Directory::Entries::Iterator& Directory::Entries::Iterator::operator ++()
{
	if (mpIterator && !mpIterator->Next())
	{
		delete mpIterator;
		mpIterator = nullptr;
	}
	return *this;
}

Directory::DirEntry Directory::Entries::Iterator::operator *() const
{
	if (mpIterator)
		return mpIterator->ToEntry();

	DirEntry result;
	result.mAttributes = 0;
	return result;
}


//////////////////////////////////////////////////////////////////////////
Directory::Entries::Entries(const String& path)
	: mPath(path)
	, mPredicate([](const DirEntry&) { return true; })
{}

Directory::Entries::Entries(const String& path, Predicate&& pred)
	: mPath(path)
	, mPredicate(Move(pred))
{}

Directory::Entries::Iterator Directory::Entries::begin()
{
	return Iterator(mPath, Move(mPredicate));
}

Directory::Entries::Iterator Directory::Entries::end()
{
	return Iterator();
}


//////////////////////////////////////////////////////////////////////////
Directory::Files::Files(const String& path)
	: Entries(path, [](const DirEntry& entry) { return (entry.mAttributes&eFile) != 0; })
{}


Directory::Files::Files(const String& path, Predicate&& pred)
	: Entries(path, [=](const DirEntry& entry)
{
	if (entry.mAttributes&eFile) { return pred(entry); } return false;
})
{
}

//////////////////////////////////////////////////////////////////////////
Directory::Directories::Directories(const String& path)
	: Entries(path, [](const DirEntry& entry) {return (entry.mAttributes&eDirectory) != 0; })
{}

Directory::Directories::Directories(const String& path, Predicate&& pred)
	: Entries(path, [=](const DirEntry& entry) {if (entry.mAttributes&eDirectory) { return pred(entry); } return false; })
{}
