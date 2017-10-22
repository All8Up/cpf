//////////////////////////////////////////////////////////////////////////
#include <gmock/gmock.h>
#include "Future.hpp"

/*
initial target for usage: s_IO::File.hpp & Stream.hpp.
API will be written as:

Future<Stream*, IOError> Create(const String& name, StreamAccess access);

Future<void, IOError> Close();
Future<void, IOError> Flush();
Future<int64_t, IOError> GetPosition();
Future<int64_t, IOError> GetLength();
Future<void, IOError> Seek(int64_t offset, StreamOrigin origin);

Future<int64_t, IOError> Read(void* outBuffer, int64_t length);
Future<int64_t, IOError> Write(const void* inBuffer, int64_t length);

// Use-case.
// Read an entire file into a buffer.
{
	IntrusivePtr<Stream> stream;
	Vector<uint8_t> buffer;
	auto test = File::Create(filename, Stream::Access::eRead)
		.Then([&](Future<IntrusivePtr<Stream>, IOError>&& result) {
			if (result.IsOK())
			{
				stream = result.GetValue();
				return stream->GetLength();
			}
			// Handle errors.
			return result;
		})
		.Then([&](Future<int64_t, IOError>&& result) {
			if (result.IsOK())
			{
				auto length = result.GetValue();
				buffer.resize(length+1);
				return stream->Read(buffer.data(), length);
			}
			// Handle errors.
			return result;
		})
		.Then([&](Future<int64_t, IOError>&& result) {
			if (result.IsOK())
			{
				buffer.back() = 0;
				return Future<void, IOError>::MakeOK();
			}
			return Future<void, IOError::MakeError(result.GetError());
		});
	test.Wait();
	if (test.IsOK())
		... use buffer data ...
	else
		... handle error ...
}
*/
