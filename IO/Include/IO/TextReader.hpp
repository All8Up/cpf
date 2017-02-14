#pragma once
#include "IO/IO.hpp"
#include "IO/Stream.hpp"
#include "IO/Reader.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class TextReader : public Reader
			{
			public:
				TextReader(Stream*);
				~TextReader() override;

				int64_t Read(bool&) override;
				int64_t Read(String&) override;
				int64_t Read(WString&) override;

				int64_t Read(char&) override;
				int64_t Read(wchar_t&) override;

				int64_t Read(int8_t&) override;
				int64_t Read(int16_t&) override;
				int64_t Read(int32_t&) override;
				int64_t Read(int64_t&) override;
				int64_t Read(uint8_t&) override;
				int64_t Read(uint16_t&) override;
				int64_t Read(uint32_t&) override;
				int64_t Read(uint64_t&) override;

				int64_t Read(float&) override;
				int64_t Read(double&) override;

				int64_t Align(int) override;
				int64_t Pad(int) override;

				operator bool() const override;

				Stream* GetStream() const override;

			private:
				StreamPtr mpStream;
			};
		}
	}
}
