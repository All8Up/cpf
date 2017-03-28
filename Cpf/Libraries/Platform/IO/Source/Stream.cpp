/**
 * @brief Implements the stream classes.
 */
#include "IO/Stream.hpp"

Cpf::Vector<char> CPF_EXPORT_IO Cpf::Platform::IO::ReadText(Stream* stream)
{
	Vector<char> result;
	int64_t streamLen = stream->GetLength();
	result.resize(streamLen);
	stream->Read(result.data(), streamLen);
	result.push_back(0);
	return result;
}

Cpf::Vector<uint8_t> CPF_EXPORT_IO Cpf::Platform::IO::ReadBinary(Stream* stream)
{
	Vector<uint8_t> result;
	int64_t streamLen = stream->GetLength();
	result.resize(streamLen);
	stream->Read(result.data(), streamLen);
	result.push_back(0);
	return result;
}
