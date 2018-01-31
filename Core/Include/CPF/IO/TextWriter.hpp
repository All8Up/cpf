#pragma once
#include "CPF/IO/Stream.hpp"


namespace CPF
{
	namespace IO
	{
		class CPF_EXPORT TextWriter
		{
		public:
			TextWriter(Stream*);
			~TextWriter();

			operator bool() const;

			Outcome<int64_t, Error> Write(const void* inBuffer, int64_t length);

			Stream* GetStream() const;

		private:
			CPF_DLL_SAFE_BEGIN
			StreamPtr mpStream;
			CPF_DLL_SAFE_END
		};
	}
}
