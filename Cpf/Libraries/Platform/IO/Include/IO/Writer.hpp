#pragma once
#include "IO/IO.hpp"
#include "IO/Stream.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class Writer
			{
			public:
				virtual ~Writer() = 0;

				virtual int64_t Write(bool&) = 0;
				virtual int64_t Write(String&) = 0;
				virtual int64_t Write(WString&) = 0;

				virtual int64_t Write(char&) = 0;
				virtual int64_t Write(wchar_t&) = 0;

				virtual int64_t Write(int8_t&) = 0;
				virtual int64_t Write(int16_t&) = 0;
				virtual int64_t Write(int32_t&) = 0;
				virtual int64_t Write(int64_t&) = 0;
				virtual int64_t Write(uint8_t&) = 0;
				virtual int64_t Write(uint16_t&) = 0;
				virtual int64_t Write(uint32_t&) = 0;
				virtual int64_t Write(uint64_t&) = 0;

				virtual int64_t Write(float&) = 0;
				virtual int64_t Write(double&) = 0;

				virtual int64_t Align(int) = 0;
				virtual int64_t Pad(int) = 0;

				virtual operator bool() const = 0;

				virtual Stream* GetStream() const = 0;
			};
		}
	}
}
