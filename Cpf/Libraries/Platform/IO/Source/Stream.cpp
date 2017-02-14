/**
 * @brief Implements the stream classes.
 */
#include "IO/Stream.hpp"

Cpf::Vector<char> CPF_EXPORT_IO Cpf::Platform::IO::ReadText(Stream* stream)
{
	Vector<char> result;
	int64_t streamLen = stream->GetLength();
	result.resize(streamLen);
	stream->Read(result.begin(), streamLen);
	result.push_back(0);
	return result;
}
