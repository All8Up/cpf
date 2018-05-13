//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/MemoryStream.hpp"
#include "CPF/CSTD/Memory.hpp"

using namespace CPF;
using namespace IO;

MemoryStream* MemoryStream::Create()
{
	return new MemoryStream();
}

MemoryStream::MemoryStream()
	: mPosition(0)
{}


Access MemoryStream::GetAccess()
{
	return Access::eBoth;
}

bool MemoryStream::CanSeek()
{
	return true;
}

bool MemoryStream::CanRead()
{
	return true;
}

bool MemoryStream::CanWrite()
{
	return true;
}

Option<Error> MemoryStream::Close()
{
	return Option<Error>::None();
}

Option<Error> MemoryStream::Flush()
{
	return Option<Error>::None();
}

Outcome<int64_t, Error> MemoryStream::GetPosition()
{
	return Outcome<int64_t, Error>::OK(mPosition);
}

Outcome<int64_t, Error> MemoryStream::GetLength()
{
	return Outcome<int64_t, Error>::OK(int64_t(mBuffer.size()));
}

Option<Error> MemoryStream::Seek(int64_t offset, Origin origin)
{
	// TODO: Add specific errors for this.
	switch (origin)
	{
	case Origin::eBegin:
		if (offset >= 0 && offset < int64_t(mBuffer.size()))
		{
			mPosition = offset;
			return Option<Error>::None();
		}
		return Option<Error>::Some(Error::eUnknownError);
	case Origin::eCurrent:
		if ((mPosition + offset) >= 0 && (mPosition + offset) < int64_t(mBuffer.size()))
		{
			mPosition += offset;
			return Option<Error>::None();
		}
		return Option<Error>::Some(Error::eUnknownError);
	case Origin::eEnd:
		if (offset > 0)
			return Option<Error>::Some(Error::eUnknownError);
		if ((int64_t(mBuffer.size()) + offset) >= 0)
		{
			mPosition = int64_t(mBuffer.size()) + offset;
			return Option<Error>::None();
		}
		return Option<Error>::Some(Error::eUnknownError);
	}
	CPF_ASSERT_ALWAYS;
	return Option<Error>::Some(Error::eUnknownError);
}

Outcome<int64_t, Error> MemoryStream::Read(void* outBuffer, int64_t length)
{
	if (mPosition <= int64_t(mBuffer.size()))
	{
		int64_t amount = int64_t(mBuffer.size()) - mPosition;
		if (length < amount)
			amount = length;
		CSTD::MemCpy(outBuffer, mBuffer.data() + mPosition, amount);
		mPosition += amount;
		return Outcome<int64_t, Error>::OK(amount);
	}
	return Outcome<int64_t, Error>::Error(Error::eOutOfMemory);
}

Outcome<int64_t, Error> MemoryStream::Write(const void* inBuffer, int64_t length)
{
	const auto newEnd = mPosition + length;
	mBuffer.resize(newEnd);
	CSTD::MemCpy(mBuffer.data() + mPosition, inBuffer, length);
	mPosition += length;
	return Outcome<int64_t, Error>::OK(length);
}

MemoryStream::operator bool() const
{
	return true;
}

void* MemoryStream::GetData()
{
	return mBuffer.data();
}

const void* MemoryStream::GetData() const
{
	return mBuffer.data();
}

size_t MemoryStream::GetSize() const
{
	return mBuffer.size();
}
