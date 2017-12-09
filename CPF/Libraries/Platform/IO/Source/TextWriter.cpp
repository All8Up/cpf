//////////////////////////////////////////////////////////////////////////
#include "IO/TextWriter.hpp"

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

int64_t TextWriter::Write(const void* inBuffer, int64_t length, Error* error)
{
	return mpStream->Write(inBuffer, length, error);
}

Stream* TextWriter::GetStream() const
{
	return mpStream;
}
