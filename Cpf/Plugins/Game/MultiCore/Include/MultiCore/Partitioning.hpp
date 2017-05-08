//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/WorkContext.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		template <typename CONTAINER, typename CALLER>
		struct EqualPartitions
		{
			static void Execute(const CONTAINER& container, const Concurrency::WorkContext* tc, CALLER* caller)
			{
				int32_t threadIndex = tc->mThreadId;
				int32_t threadCount = tc->mpScheduler->GetActiveThreads();
				int32_t workCount = int32_t(container.GetSize());
				int32_t partitionSize = int32_t(workCount) / threadCount;
				int32_t start = threadIndex * partitionSize;
				int32_t end = start + partitionSize;
				int32_t overflow = workCount - (threadCount*partitionSize);
				if (overflow > 0 && threadIndex == 0)
					end += overflow;

				for (int i = start; i < end; ++i)
				{
					const auto& work = container[i];
					caller->Execute(tc, work);
				}
			}
		};
	}
}
