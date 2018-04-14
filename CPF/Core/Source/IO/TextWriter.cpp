//////////////////////////////////////////////////////////////////////////
#include "CPF/IO/TextWriter.hpp"

using namespace CPF;
using namespace IO;

//////////////////////////////////////////////////////////////////////////
TextWriter::TextWriter(Stream* strm)
	: mpStream(strm)
{
	mpStream->AddRef();
}

TextWriter::~TextWriter()
{}

TextWriter::operator bool() const
{
	return bool(mpStream);
}

Outcome<int64_t, Error> TextWriter::Write(const void* inBuffer, int64_t length)
{
	return mpStream->Write(inBuffer, length);
}

Stream* TextWriter::GetStream() const
{
	return mpStream;
}
