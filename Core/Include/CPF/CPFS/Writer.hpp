//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/CPFS/Header.hpp"
#include "CPF/CPFS/Chunk.hpp"
#include "CPF/IO/Stream.hpp"
#include "CPF/IO/MemoryStream.hpp"

namespace CPF
{
	namespace CPFS
	{
		class Writer
		{
		public:
			Writer(IO::Stream& outStream);
			Writer(Writer&&) = delete;
			Writer(const Writer&) = delete;

			Writer& operator = (Writer&&) = delete;
			Writer& operator = (const Writer&) = delete;

			bool Begin(HeaderFlags flags = HeaderFlags::eNone) const;
			bool End() const;

			IO::Stream* Descend(ECC type, Version version = Chunk::kDefaultVersion, ChunkFlags flags = ChunkFlags::eNone);
			bool Ascend();

		private:
			IO::Stream& mStream;
			using ChunkData = STD::Pair<Chunk, IntrusivePtr<IO::MemoryStream>>;
			using ChunkStack = STD::Vector<ChunkData>;
			ChunkStack mChunkStack;
		};

		//////////////////////////////////////////////////////////////////////////
		inline Writer::Writer(IO::Stream& outStream)
			: mStream(outStream)
		{
		}

		inline bool Writer::Begin(HeaderFlags flags) const
		{
			Header header =
			{
				Header::kMagic,
				Header::kVersion,
				0,
				flags
			};
			int64_t writeLen = 0;
			return mStream.Write(&header, sizeof(header)).CheckOK(writeLen) && writeLen == sizeof(header);
		}

		inline bool Writer::End() const
		{
			return mStream.Flush().IsNone();
		}

		inline IO::Stream* Writer::Descend(ECC type, Version version, ChunkFlags flags)
		{
			const Chunk chunk =
			{
				type,
				version,
				flags,
				0
			};
			const ChunkData chunkData{ chunk, IntrusivePtr<IO::MemoryStream>(IO::MemoryStream::Create()) };
			mChunkStack.push_back(chunkData);

			return mChunkStack.back().second;
		}

		inline bool Writer::Ascend()
		{
			auto memorySize = mChunkStack.back().second->GetSize();
			auto alignSize = memorySize + (alignof(Chunk)-1);
			alignSize = (alignSize / alignof(Chunk)) * alignof(Chunk);
			const auto padSize = alignSize - memorySize;

			// The chunk length is the actual data length, not the aligned and padded length.
			mChunkStack.back().first.mLength = memorySize;

			// Pad the memory stream if required.
			int64_t writeSize = 0;
			if (padSize > 0)
			{
				STD::Vector<uint8_t> zeros(padSize);
				if (mChunkStack.back().second->Write(zeros.data(), padSize).CheckOK(writeSize) && writeSize == int64_t(padSize))
				{
					memorySize += padSize;
				}
				else
					return false;
			}

			// Write the chunk and then the memory stream.
			if (mStream.Write(&mChunkStack.back().first, sizeof(Chunk)).CheckOK(writeSize) && writeSize == int64_t(sizeof(Chunk)))
			{
				if (mStream.Write(mChunkStack.back().second->GetData(), memorySize).CheckOK(writeSize) && writeSize == int64_t(memorySize))
				{
					mChunkStack.pop_back();
					return true;
				}
			}

			return false;
		}
	}
}
