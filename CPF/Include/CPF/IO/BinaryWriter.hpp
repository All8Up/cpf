#pragma once
#include "CPF/IO/Stream.hpp"

namespace CPF
{
	namespace IO
	{
		class BinaryWriter
		{
		public:
			BinaryWriter(Stream*);
			~BinaryWriter();

			int64_t Write(bool&);
			int64_t Write(String&);
			int64_t Write(WString&);

			int64_t Write(char&);
			int64_t Write(wchar_t&);

			int64_t Write(int8_t&);
			int64_t Write(int16_t&);
			int64_t Write(int32_t&);
			int64_t Write(int64_t&);
			int64_t Write(uint8_t&);
			int64_t Write(uint16_t&);
			int64_t Write(uint32_t&);
			int64_t Write(uint64_t&);

			int64_t Write(float&);
			int64_t Write(double&);

			int64_t Align(int);
			int64_t Pad(int);

			operator bool() const;

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}