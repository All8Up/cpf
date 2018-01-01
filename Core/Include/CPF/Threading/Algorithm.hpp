//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Threading.hpp"
#include <atomic>

namespace CPF
{
	namespace Threading
	{
		template <typename DATA, typename IndexType, typename UnaryFunction>
		void ChunkIndexedForEach(const DATA& data, std::atomic<IndexType>& first, IndexType last, UnaryFunction callable, int ChunkSize = 32)
		{
			IndexType start;
			do
			{
				start = first.fetch_add(ChunkSize);
				for (; start < last; ++start)
				{
					callable(data[start]);
				}
			} while (start < last);
		}
	}
}
