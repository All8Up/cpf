//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO/Stream.hpp"

namespace CPF
{
	namespace IO
	{
		class MemoryStream : public tRefCounted<Stream>
		{
		public:
			//
			static MemoryStream* Create();

			//
			MemoryStream(MemoryStream&&) = default;
			MemoryStream(const MemoryStream&) = default;

			MemoryStream& operator =(MemoryStream&&) = default;
			MemoryStream& operator =(const MemoryStream&) = default;

			// Overrides from Stream.
			Access GetAccess() override;
			bool CanSeek() override;
			bool CanRead() override;
			bool CanWrite() override;

			//
			Option<Error> Close() override;
			Option<Error> Flush() override;
			Outcome<int64_t, Error> GetPosition() override;
			Outcome<int64_t, Error> GetLength() override;
			Option<Error> Seek(int64_t offset, Origin origin) override;

			//
			Outcome<int64_t, Error> Read(void* outBuffer, int64_t length) override;
			Outcome<int64_t, Error> Write(const void* inBuffer, int64_t length) override;

			//
			operator bool() const override;

			// Memory specific functionality.
			void* GetData();
			const void* GetData() const;
			size_t GetSize() const;

		private:
			MemoryStream();
			~MemoryStream() = default;

			STD::Vector<uint8_t> mBuffer;
			int64_t mPosition;
		};
	}
}
