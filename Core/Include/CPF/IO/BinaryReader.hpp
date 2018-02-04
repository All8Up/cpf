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

			int64_t Read(bool&) const;
			int64_t Read(String&) const;
			int64_t Read(WString&) const;
			int64_t Read(Std::Utf8String&) const;

			int64_t Read(char&) const;
			int64_t Read(wchar_t&) const;

			int64_t Read(int8_t&) const;
			int64_t Read(int16_t&) const;
			int64_t Read(int32_t&) const;
			int64_t Read(int64_t&) const;
			int64_t Read(uint8_t&) const;
			int64_t Read(uint16_t&) const;
			int64_t Read(uint32_t&) const;
			int64_t Read(uint64_t&) const;

			int64_t Read(float&) const;
			int64_t Read(double&) const;

			int64_t Align(int) const;
			int64_t Pad(int) const;

			operator bool() const;

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}
