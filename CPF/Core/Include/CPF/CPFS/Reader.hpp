//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/CPFS/Header.hpp"
#include "CPF/CPFS/Chunk.hpp"
#include "CPF/IO/Stream.hpp"

namespace CPF
{
	namespace CPFS
	{
		class Reader
		{
		public:
			Reader(IO::Stream& stream);
			Reader(Reader&&) = delete;
			Reader(const Reader&) = delete;

			Reader& operator =(Reader&&) = delete;
			Reader& operator =(const Reader&) = delete;

			bool Begin() const;
			bool Descend(Chunk& chunk) const;
			bool Read(void* buffer, int64_t size) const;

		private:
			IO::Stream& mStream;
		};


		inline Reader::Reader(IO::Stream& stream)
			: mStream(stream)
		{
		}

		inline bool Reader::Begin() const
		{
			CPF_ASSERT(mStream.CanRead());
			Header header;
			int64_t readSize = 0;
			if (mStream.Read(&header, sizeof(header)).CheckOK(readSize) && readSize == sizeof(header))
			{
				if (header.mMagic == Header::kMagic)
				{
					return true;
				}
			}
			return false;
		}

		inline bool Reader::Descend(Chunk& chunk) const
		{
			int64_t readSize = 0;
			return mStream.Read(&chunk, sizeof(chunk)).CheckOK(readSize) && readSize == sizeof(chunk);
		}

		inline bool Reader::Read(void* buffer, int64_t size) const
		{
			int64_t readSize = 0;
			return mStream.Read(buffer, size).CheckOK(readSize) && readSize == size;
		}
	}
}
