/**
 * @brief Declares the stream class.
 */
#pragma once
#include "CPF/IO.hpp"
#include "CPF/iRefCounted.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/Option.hpp"

namespace CPF
{
	namespace IO
	{
		// Forward references.
		class Stream;
		using StreamPtr = IntrusivePtr<Stream>;


		/** @brief Base class for streams. */
		class Stream : public iRefCounted
		{
		public:
			//
			using Access = IO::Access;
			using Origin = IO::Origin;

			//
			virtual Access GetAccess() = 0;
			virtual bool CanSeek() = 0;
			virtual bool CanRead() = 0;
			virtual bool CanWrite() = 0;

			//
			virtual Option<Error> Close() = 0;
			virtual Option<Error> Flush() = 0;
			virtual Outcome<int64_t, Error> GetPosition() = 0;
			virtual Outcome<int64_t, Error> GetLength() = 0;
			virtual Option<Error> Seek(int64_t offset, Origin origin) = 0;

			//
			virtual Outcome<int64_t, Error> Read(void* outBuffer, int64_t length) = 0;
			virtual Outcome<int64_t, Error> Write(const void* inBuffer, int64_t length) = 0;

			//
			virtual operator bool() const = 0;

		protected:
			//
			virtual ~Stream() {}
		};

		/** @brief Utility to read the contents of a stream as a text file. */
		using ReadTextOutcome = Outcome<String, Error>;
		ReadTextOutcome CPF_EXPORT ReadText(Stream*);

		using ReadBinaryOutcome = Outcome<Vector<uint8_t>, IO::Error>;
		ReadBinaryOutcome CPF_EXPORT ReadBinary(Stream*);
	}
}
