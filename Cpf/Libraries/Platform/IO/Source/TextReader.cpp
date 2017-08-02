//////////////////////////////////////////////////////////////////////////
#include "IO/TextReader.hpp"

using namespace Cpf;
using namespace Platform;
using namespace IO;


//////////////////////////////////////////////////////////////////////////
TextReader::TextReader(Stream* strp)
	: mpStream(strp)
{
	mpStream->AddRef();
}

TextReader::~TextReader()
{}

int64_t TextReader::Read(bool& b)
{
	uint32_t temp;
	auto result = mpStream->Read(&temp, sizeof(uint32_t));
	b = temp ? 1 : 0;
	return result;
}

int64_t TextReader::Read(String& s)
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

int64_t TextReader::Read(WString& s)
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

int64_t TextReader::Read(char& c)
{
	return mpStream->Read(&c, sizeof(c));
}

int64_t TextReader::Read(wchar_t& c)
{
	return mpStream->Read(&c, sizeof(c));
}

int64_t TextReader::Read(int8_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(int16_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(int32_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(int64_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(uint8_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(uint16_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(uint32_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(uint64_t& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(float& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Read(double& v)
{
	return mpStream->Read(&v, sizeof(v));
}

int64_t TextReader::Align(int a)
{
	CPF_ASSERT((a & (a - 1)) == 0);
	auto current = mpStream->GetPosition();
	auto offset = (current + (a - 1)) & (a - 1);

	uint8_t v = 0;
	for (auto i = 0; i < offset; ++i)
		mpStream->Read(&v, 1);

	return *this;
}

int64_t TextReader::Pad(int v)
{
	for (auto i = 0; i < v; ++i)
		mpStream->Read(&v, 1);
	return v;
}


TextReader::operator bool() const
{
	return bool(mpStream);
}

Stream* TextReader::GetStream() const
{
	return mpStream;
}

int64_t TextReader::ReadLine(String& out)
{
	int64_t result = 0;
	int64_t state = 0;
	uint8_t current;
	out.clear();
	while ((state = Read(current)))
	{
		if (current == 0x0d || current == 0x0a)
		{
			if (current == 0x0d)
				continue;  // Skip it.
			break;
		}
		else
		{
			++result;
			out += current;
		}
	}
	return result;
}

int64_t TextReader::ReadAll(String& out)
{
	int64_t result = 0;
	out.clear();
	uint8_t current;
	int64_t state = 0;
	while ((state = Read(current)))
	{
		++result;
		out += current;
	}
	return result;
}
