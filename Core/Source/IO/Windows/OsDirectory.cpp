//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/Directory.hpp"
#include "CPF/IO/Path.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/Std/Memory.hpp"


using namespace CPF;
using namespace IO;

CPF_EXPORT void Directory::SetWorkingDirectory(const String& dir)
{
	::SetCurrentDirectoryA(dir.c_str());
}


CPF_EXPORT String Directory::GetWorkingDirectory()
{
	String result;
	auto required = ::GetCurrentDirectoryA(0, nullptr);
	result.resize(required, ' ');
	::GetCurrentDirectoryA(DWORD(result.size()), &result[0]);
	result.pop_back();
	return result;
}


CPF_EXPORT bool Directory::OsExists(const String& dir)
{
	DWORD ftype = GetFileAttributesA(dir.c_str());
	if (ftype == INVALID_FILE_ATTRIBUTES)
		return false;
	if (ftype & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	return false;
}


CPF_EXPORT bool Directory::OsCreate(const String& dir)
{
	return ::CreateDirectoryA(dir.c_str(), nullptr)!=0;
}


CPF_EXPORT bool Directory::OsDelete(const String& dir)
{
	return ::RemoveDirectoryA(dir.c_str())!=0;
}



//////////////////////////////////////////////////////////////////////////
struct Directory::Entries::OsIterator
{
	OsIterator()
		: mFind(INVALID_HANDLE_VALUE)
	{
		Std::MemSet(&mFindData, 0, sizeof(mFindData));
	}
	~OsIterator()
	{
		if (mFind != INVALID_HANDLE_VALUE)
			::FindClose(mFind);
	}

	bool Init(const String& path, Predicate&& pred)
	{
		String searchPath = Path::Combine(Path::ToOS(Path::Normalize(path)), "*");
		mPredicate = Move(pred);

		mFind = ::FindFirstFileA(searchPath.c_str(), &mFindData);
		if (mFind != INVALID_HANDLE_VALUE)
		{
			if (!mPredicate(ToEntry()))
				return Next();
			return true;
		}
		return false;
	}

	bool Next()
	{
		bool more = true;
		do
		{
			more = ::FindNextFileA(mFind, &mFindData) == TRUE ? true : false;
		} while (more && !mPredicate(ToEntry()));
		return more;
	}

	DirEntry ToEntry() const
	{
		DirEntry result;

		result.mName = mFindData.cFileName;
		result.mAttributes = Attributes::eNone;
		if (mFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			result.mAttributes |= Attributes::eDirectory;
		else
			result.mAttributes |= Attributes::eFile;

		return result;
	}

	HANDLE mFind;
	WIN32_FIND_DATAA mFindData;
	Predicate mPredicate;
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
	result.mAttributes = Attributes::eNone;
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
	: Entries(path, [](const DirEntry& entry) { return IsSet(entry.mAttributes, Attributes::eFile); })
{}


Directory::Files::Files(const String& path, Predicate&& pred)
	: Entries(path, [=](const DirEntry& entry)
	{
		if (IsSet(entry.mAttributes, Attributes::eFile))
		{
			return pred(entry);
		}
		return false;
	})
{
}

//////////////////////////////////////////////////////////////////////////
Directory::Directories::Directories(const String& path)
	: Entries(path, [](const DirEntry& entry) {return IsSet(entry.mAttributes, Attributes::eDirectory); })
{}

Directory::Directories::Directories(const String& path, Predicate&& pred)
	: Entries(path, [=](const DirEntry& entry) {if (IsSet(entry.mAttributes, Attributes::eDirectory)) { return pred(entry); } return false; })
{}
