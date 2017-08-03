/**
 * @brief Implements the stream classes.
 */
#include "IO/Stream.hpp"

using namespace Cpf;

Vector<char> CPF_EXPORT_IO IO::ReadText(Stream* stream)
{
	Vector<char> result;
	int64_t streamLen = stream->GetLength();
	result.resize(streamLen);
	stream->Read(result.data(), streamLen);
	result.push_back(0);
	return result;
}

Vector<uint8_t> CPF_EXPORT_IO IO::ReadBinary(Stream* stream)
{
	Vector<uint8_t> result;
	if (stream)
	{
		int64_t streamLen = stream->GetLength();
		result.resize(streamLen);
		stream->Read(result.data(), streamLen);
	}
	return result;
}
