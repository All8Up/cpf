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
			class Reader
			{
			public:
				virtual ~Reader() = 0;

				virtual int64_t Read(bool&) = 0;
				virtual int64_t Read(String&) = 0;
				virtual int64_t Read(WString&) = 0;

				virtual int64_t Read(char&) = 0;
				virtual int64_t Read(wchar_t&) = 0;

				virtual int64_t Read(int8_t&) = 0;
				virtual int64_t Read(int16_t&) = 0;
				virtual int64_t Read(int32_t&) = 0;
				virtual int64_t Read(int64_t&) = 0;
				virtual int64_t Read(uint8_t&) = 0;
				virtual int64_t Read(uint16_t&) = 0;
				virtual int64_t Read(uint32_t&) = 0;
				virtual int64_t Read(uint64_t&) = 0;

				virtual int64_t Read(float&) = 0;
				virtual int64_t Read(double&) = 0;

				virtual int64_t Align(int) = 0;
				virtual int64_t Pad(int) = 0;

				virtual operator bool() const = 0;

				virtual Stream* GetStream() const = 0;
			};
		}
	}
}
