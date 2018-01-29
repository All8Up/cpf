#pragma once
#include "CPF/IO/Stream.hpp"
#include "CPF/Std/Utf8String.hpp"

namespace CPF
{
	namespace IO
	{
		class BinaryReader
		{
		public:
			BinaryReader(Stream*);
			~BinaryReader();

			int64_t Read(bool&);
			int64_t Read(String&);
			int64_t Read(WString&);
			int64_t Read(Std::Utf8String&);

			int64_t Read(char&);
			int64_t Read(wchar_t&);

			int64_t Read(int8_t&);
			int64_t Read(int16_t&);
			int64_t Read(int32_t&);
			int64_t Read(int64_t&);
			int64_t Read(uint8_t&);
			int64_t Read(uint16_t&);
			int64_t Read(uint32_t&);
			int64_t Read(uint64_t&);

			int64_t Read(float&);
			int64_t Read(double&);

			int64_t Align(int);
			int64_t Pad(int);

			operator bool() const;

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}
