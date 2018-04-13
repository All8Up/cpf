/**
 * @brief Implements the stream classes.
 */
#include "CPF/IO/Stream.hpp"

using namespace CPF;

IO::ReadTextOutcome CPF_EXPORT IO::ReadText(Stream* stream)
{
	STD::String result;

	auto length = stream->GetLength();
	int64_t streamLen;
	if (length.CheckOK(streamLen))
	{
		result.resize(streamLen);

		int64_t readLen;
		auto readResult = stream->Read(&result[0], streamLen);
		if (readResult.CheckOK(readLen))
		{
			result.push_back(0);
			return ReadTextOutcome::OK(result);
		}
	}
	return ReadTextOutcome::Error(length.GetError());
}

IO::ReadBinaryOutcome CPF_EXPORT IO::ReadBinary(Stream* stream)
{
	STD::Vector<uint8_t> result;
	if (stream)
	{
		int64_t streamLen;
		auto lengthResult = stream->GetLength();
		if (lengthResult.CheckOK(streamLen))
		{
			result.resize(streamLen);

			stream->Read(result.data(), streamLen);
			return ReadBinaryOutcome::OK(result);
		}
	}
	return ReadBinaryOutcome::Error(Error::eInvalidFile);
}
