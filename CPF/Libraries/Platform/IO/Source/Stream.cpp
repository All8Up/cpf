/**
 * @brief Implements the stream classes.
 */
#include "IO/Stream.hpp"

using namespace CPF;

String CPF_EXPORT_IO IO::ReadText(Stream* stream)
{
	String result;
	const int64_t streamLen = stream->GetLength();
	result.resize(streamLen);
	stream->Read(&result[0], streamLen);
	result.push_back(0);
	return result;
}

Vector<uint8_t> CPF_EXPORT_IO IO::ReadBinary(Stream* stream)
{
	Vector<uint8_t> result;
	if (stream)
	{
		const int64_t streamLen = stream->GetLength();
		result.resize(streamLen);
		stream->Read(result.data(), streamLen);
	}
	return result;
}
