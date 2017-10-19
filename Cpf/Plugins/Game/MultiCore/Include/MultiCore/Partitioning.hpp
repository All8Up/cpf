//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/WorkContext.hpp"
#include "Atomic/Atomic.hpp"

namespace CPF
{
	namespace MultiCore
	{
		template <typename CONTAINER, typename CALLER>
		struct Partitions
		{
			static constexpr uint32_t kDivisionSize = 10;
			struct Context
			{
				uint32_t mIndex = 0;
			};

			static void Begin(Context& context) { Atomic::Store(context.mIndex, 0); }
			static void End(Context&) {}

			static void Execute(const CONTAINER& container, const Concurrency::WorkContext* tc, Context* context, CALLER* caller)
			{
				uint32_t workCount = uint32_t(container.GetSize());
				for (uint32_t lastIndex = Atomic::Add(context->mIndex, kDivisionSize),
					firstIndex = lastIndex - kDivisionSize;
					firstIndex < workCount;
					lastIndex = Atomic::Add(context->mIndex, kDivisionSize),
					firstIndex = lastIndex - kDivisionSize
					)
				{
					for (uint32_t i = firstIndex; i<workCount && i<lastIndex; ++i)
					{
						const auto& work = container[i];
						caller->Execute(tc, work);
					}
				}
			}
		};

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
