#pragma once
#include "IO/Stream.hpp"


namespace Cpf
{
	namespace IO
	{
		class TextWriter
		{
		public:
			TextWriter(Stream*);
			~TextWriter();

			operator bool() const;

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}
