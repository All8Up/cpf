//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/Directory.hpp"
#include "CPF/IO/Path.hpp"
#include "CPF/Std/Move.hpp"
#include "CPF/CSTD/Memory.hpp"


using namespace CPF;
using namespace IO;

CPF_EXPORT void Directory::SetWorkingDirectory(const STD::Utf8String& dir)
{
	STD::WString wstr;
	ConvertUtf8To16(dir, wstr);
	::SetCurrentDirectoryW(wstr.c_str());
}


CPF_EXPORT STD::Utf8String Directory::GetWorkingDirectory()
{
	STD::String result;
	auto required = ::GetCurrentDirectoryA(0, nullptr);
	result.resize(required, ' ');
	::GetCurrentDirectoryA(DWORD(result.size()), &result[0]);
	result.pop_back();
	return result;
}


CPF_EXPORT bool Directory::OsExists(const STD::Utf8String& dir)
{
	DWORD ftype = GetFileAttributesA(dir.data().c_str());
	if (ftype == INVALID_FILE_ATTRIBUTES)
		return false;
	if (ftype & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	return false;
}


CPF_EXPORT bool Directory::OsCreate(const STD::Utf8String& dir)
{
	return ::CreateDirectoryA(dir.data().c_str(), nullptr)!=0;
}


CPF_EXPORT bool Directory::OsDelete(const STD::Utf8String& dir)
{
	return ::RemoveDirectoryA(dir.data().c_str())!=0;
}

CPF_EXPORT Option<char*> Directory::OsGetError()
{
	const DWORD errorValue = GetLastError();
	if (errorValue!=0)
	{
		LPSTR buffer = nullptr;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			errorValue,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPTSTR>(&buffer),
			0,
			nullptr
		);
		return Option<char*>::Some(buffer);
	}
	return Option<char*>::None();
}

CPF_EXPORT void Directory::OsFreeError(char* errorString)
{
	LocalFree(errorString);
}


//////////////////////////////////////////////////////////////////////////
struct Directory::Entries::OsIterator
{
	OsIterator()
		: mFind(INVALID_HANDLE_VALUE)
	{
		CSTD::MemSet(&mFindData, 0, sizeof(mFindData));
	}
	~OsIterator()
	{
		if (mFind != INVALID_HANDLE_VALUE)
			::FindClose(mFind);
	}

	bool Init(const STD::String& path, Predicate&& pred)
	{
		STD::Utf8String searchPath = Path::Combine(Path::ToOS(Path::Normalize(path)), "*");
		mPredicate = STD::Move(pred);
		
		STD::WString searchString;
		ConvertUtf8To16(searchPath, searchString);

		mFind = ::FindFirstFileW(searchString.c_str(), &mFindData);
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
			more = ::FindNextFileW(mFind, &mFindData) == TRUE ? true : false;
		} while (more && !mPredicate(ToEntry()));
		return more;
	}

	DirEntry ToEntry() const
	{
		DirEntry result;

		result.mName = STD::Utf8String(mFindData.cFileName);
		result.mAttributes = Attributes::eNone;
		if (mFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			result.mAttributes |= Attributes::eDirectory;
		else
			result.mAttributes |= Attributes::eFile;

		return result;
	}

	HANDLE mFind;
	WIN32_FIND_DATAW mFindData;
	Predicate mPredicate;
};



//////////////////////////////////////////////////////////////////////////
Directory::Entries::Iterator::Iterator()
	: mpIterator(nullptr)
{
}

Directory::Entries::Iterator::Iterator(const STD::Utf8String& path, Predicate&& pred)
	: mpIterator(new OsIterator)
{
	if (mpIterator)
	{
		if (!mpIterator->Init(path.data(), STD::Move(pred)))
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
Directory::Entries::Entries(const STD::Utf8String& path)
	: mPath(path.data())
	, mPredicate([](const DirEntry&) { return true; })
{}

Directory::Entries::Entries(const STD::Utf8String& path, Predicate&& pred)
	: mPath(path.data())
	, mPredicate(STD::Move(pred))
{}

Directory::Entries::Iterator Directory::Entries::begin()
{
	return Iterator(mPath, STD::Move(mPredicate));
}

Directory::Entries::Iterator Directory::Entries::end()
{
	return Iterator();
}


//////////////////////////////////////////////////////////////////////////
Directory::Files::Files(const STD::Utf8String& path)
	: Entries(path, [](const DirEntry& entry) { return IsSet(entry.mAttributes, Attributes::eFile); })
{}


Directory::Files::Files(const STD::Utf8String& path, Predicate&& pred)
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
Directory::Directories::Directories(const STD::Utf8String& path)
	: Entries(path, [](const DirEntry& entry) {return IsSet(entry.mAttributes, Attributes::eDirectory); })
{}

Directory::Directories::Directories(const STD::Utf8String& path, Predicate&& pred)
	: Entries(path, [=](const DirEntry& entry) {if (IsSet(entry.mAttributes, Attributes::eDirectory)) { return pred(entry); } return false; })
{}
