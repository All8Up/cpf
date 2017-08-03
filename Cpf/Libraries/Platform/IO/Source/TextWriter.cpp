//////////////////////////////////////////////////////////////////////////
#include "IO/TextWriter.hpp"

using namespace Cpf;
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

Stream* TextWriter::GetStream() const
{
	return mpStream;
}
