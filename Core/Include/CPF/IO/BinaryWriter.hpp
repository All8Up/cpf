#pragma once
#include "CPF/IO/Stream.hpp"
#include "CPF/Std/Utf8String.hpp"

namespace CPF
{
	namespace IO
	{
		class BinaryWriter
		{
		public:
			BinaryWriter(Stream*);
			~BinaryWriter();

			int64_t Write(bool&) const;
			int64_t Write(STD::String&) const;
			int64_t Write(STD::WString&) const;
			int64_t Write(STD::Utf8String&) const;

			int64_t Write(char&) const;
			int64_t Write(wchar_t&) const;

			int64_t Write(int8_t&) const;
			int64_t Write(int16_t&) const;
			int64_t Write(int32_t&) const;
			int64_t Write(int64_t&) const;
			int64_t Write(uint8_t&) const;
			int64_t Write(uint16_t&) const;
			int64_t Write(uint32_t&) const;
			int64_t Write(uint64_t&) const;

			int64_t Write(float&) const;
			int64_t Write(double&) const;

			int64_t Align(int) const;
			int64_t Pad(int) const;

			operator bool() const;

			Stream* GetStream() const;

		private:
			StreamPtr mpStream;
		};
	}
}