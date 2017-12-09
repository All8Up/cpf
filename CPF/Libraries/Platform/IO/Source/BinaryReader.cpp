//////////////////////////////////////////////////////////////////////////
#include "IO/BinaryReader.hpp"

using namespace CPF;
using namespace IO;


//////////////////////////////////////////////////////////////////////////
BinaryReader::BinaryReader(Stream* strp)
	: mpStream(strp)
{}

BinaryReader::~BinaryReader()
{}

int64_t BinaryReader::Read(bool& b)
{
	uint32_t temp;
	auto result = mpStream->Read(&temp, sizeof(uint32_t));
	b = temp ? 1 : 0;
	return result;
}

int64_t BinaryReader::Read(String& s)
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

int64_t BinaryReader::Read(WString& s)
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

int64_t BinaryReader::Read(char& c)
{
	return mpStream->Read(&c, sizeof(c));
}

int64_t BinaryReader::Read(wchar_t& c)
{
	return mpStream->Read(&c, sizeof(c));
}

int64_t BinaryReader::Read(int8_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(int16_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(int32_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(int64_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(uint8_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(uint16_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(uint32_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(uint64_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(float& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Read(double& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t BinaryReader::Align(int a)
{
	CPF_ASSERT((a & (a - 1)) == 0);
	auto current = mpStream->GetPosition();
	auto offset = (current + (a - 1)) & (a - 1);

	uint8_t v = 0;
	for (auto i = 0; i < offset; ++i)
		mpStream->Read(&v, 1);

	return *this;
}

int64_t BinaryReader::Pad(int v)
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
