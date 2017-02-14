#pragma once
#include "IO/IO.hpp"
#include "IO/Stream.hpp"
#include "IO/Writer.hpp"


namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			class BinaryWriter : public Writer
			{
			public:
				BinaryWriter(Stream*);
				~BinaryWriter() override;

				int64_t Write(bool&) override;
				int64_t Write(String&) override;
				int64_t Write(WString&) override;

				int64_t Write(char&) override;
				int64_t Write(wchar_t&) override;

				int64_t Write(int8_t&) override;
				int64_t Write(int16_t&) override;
				int64_t Write(int32_t&) override;
				int64_t Write(int64_t&) override;
				int64_t Write(uint8_t&) override;
				int64_t Write(uint16_t&) override;
				int64_t Write(uint32_t&) override;
				int64_t Write(uint64_t&) override;

				int64_t Write(float&) override;
				int64_t Write(double&) override;

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