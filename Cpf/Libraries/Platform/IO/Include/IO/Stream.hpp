/**
 * @brief Declares the stream class.
 */
#pragma once
#include "IO/IO.hpp"
#include "IntrusivePtr.hpp"
#include "Functional.hpp"
#include "Vector.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			// Forward references.
			class Stream;
			using StreamPtr = IntrusivePtr<Stream>;


			/** @brief Stream access enumeration. */
			enum class StreamAccess : int64_t
			{
				eRead,
				eWrite,
				eBoth
			};


			/** @brief Relative origin enumeration */
			enum class StreamOrigin : int64_t
			{
				eBegin,
				eEnd,
				eCurrent
			};


			/** @brief Base class for streams. */
			class Stream : public iRefCounted
			{
			public:
				//
				using Access = StreamAccess;
				using Origin = StreamOrigin;

				//
				virtual Access GetAccess() = 0;
				virtual bool CanSeek() = 0;
				virtual bool CanRead() = 0;
				virtual bool CanWrite() = 0;
				virtual bool CanTimeout() = 0;

				//
				virtual void Close(Error* error = nullptr) = 0;
				virtual void Flush(Error* error = nullptr) = 0;
				virtual int64_t GetPosition(Error* error = nullptr) = 0;
				virtual int64_t GetLength(Error* error = nullptr) = 0;
				virtual void Seek(int64_t offset, StreamOrigin origin, Error* error = nullptr) = 0;

				//
				virtual int64_t Read(void* outBuffer, int64_t length, Error* error = nullptr) = 0;
				virtual int64_t Write(const void* inBuffer, int64_t length, Error* error = nullptr) = 0;

				//
				virtual void CopyTo(Stream* target, Error* error = nullptr) const = 0;

				//
				virtual operator bool() const = 0;

			protected:
				//
				virtual ~Stream() {}
			};

			/** @brief Utility to read the contents of a stream as a text file. */
			Vector<char> CPF_EXPORT_IO ReadText(Stream*);
		}
	}
}
