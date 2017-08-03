#pragma once
#include "IO/Stream.hpp"

namespace Cpf
{
	namespace IO
	{
		class TextReader
		{
		public:
			TextReader(Stream*);
			~TextReader();

			operator bool() const;

			Stream* GetStream() const;

			// Text reader unique functions.
			int64_t ReadLine(String& out);
			int64_t ReadAll(String& out);

		private:
			StreamPtr mpStream;
		};
	}
}
