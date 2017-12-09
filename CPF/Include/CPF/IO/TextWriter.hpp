#pragma once
#include "CPF/IO/Stream.hpp"


namespace CPF
{
	namespace IO
	{
		class TextWriter
		{
		public:
			TextWriter(Stream*);
			~TextWriter();

			operator bool() const;

			int64_t Write(const void* inBuffer, int64_t length, Error* error = nullptr);

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}
