//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/BinaryReader.hpp"

using namespace CPF;
using namespace IO;


//////////////////////////////////////////////////////////////////////////
BinaryReader::BinaryReader(Stream* strp)
	: mpStream(strp)
{}

BinaryReader::~BinaryReader()
{}

int64_t BinaryReader::Read(bool& b) const
{
	uint32_t temp;
	auto result = mpStream->Read(&temp, sizeof(uint32_t));
	b = temp ? 1 : 0;
	return result.GetOK();
}

int64_t BinaryReader::Read(String& s) const
{
	// Serialize the size.
	uint32_t size;
	Read(size);

	// Resize the string.
	s.resize(size);

	// Read the string content.
	for (uint32_t i = 0; i < size; ++i)
		Read(s[i]);

	return size + 4;
}

int64_t BinaryReader::Read(WString& s) const
{
	// Serialize the size.
	uint32_t size;
	Read(size);

	// Resize the string.
	s.resize(size);

	// Read the string content.
	for (uint32_t i = 0; i < size; ++i)
		Read(s[i]);

	return size + 4;
}

int64_t BinaryReader::Read(Std::Utf8String& source) const
{
	// Serialize the size.
	uint32_t size;
	Read(size);

	// Resize the string.
	source.data().resize(size);

	// Read the string content.
	for (uint32_t i = 0; i < size; ++i)
	{
		uint8_t c;
		Read(c);
		source.data().push_back(c);
	}

	return size + 4;
}

int64_t BinaryReader::Read(char& c) const
{
	return mpStream->Read(&c, sizeof(c)).GetOK();
}

int64_t BinaryReader::Read(wchar_t& c) const
{
	return mpStream->Read(&c, sizeof(c)).GetOK();
}

int64_t BinaryReader::Read(int8_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(int16_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(int32_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(int64_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(uint8_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(uint16_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(uint32_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(uint64_t& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(float& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Read(double& v) const
{
	return mpStream->Read(&v, sizeof(v)).GetOK();
}

int64_t BinaryReader::Align(int a) const
{
	CPF_ASSERT((a & (a - 1)) == 0);
	auto current = mpStream->GetPosition();
	auto offset = (current.GetOK() + (a - 1)) & (a - 1);

	uint8_t v = 0;
	for (auto i = 0; i < offset; ++i)
		mpStream->Read(&v, 1);

	return *this;
}

int64_t BinaryReader::Pad(int v) const
{
	for (auto i = 0; i < v; ++i)
		mpStream->Read(&v, 1);
	return v;
}

BinaryReader::operator bool() const
{
	return bool(mpStream);
}

Stream* BinaryReader::GetStream() const
{
	return mpStream;
}
