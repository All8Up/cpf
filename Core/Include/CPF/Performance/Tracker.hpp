//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Hash/Crc.hpp"

namespace CPF
{
	namespace Performance
	{
		class CPF_EXPORT Tracker
		{
		public:
			static void BeginBlock(int32_t group, const char* groupName, int32_t section, const char* sectionName);
			static void EndBlock(int32_t group, int32_t section);
		};

		template <int32_t Group, int32_t Section>
		void BeginBlock(const char* groupName, const char* sectionName)
		{
			Tracker::BeginBlock(Group, groupName, Section, sectionName);
		}

		template <int32_t Group, int32_t Section>
		void EndBlock()
		{
			Tracker::EndBlock(Group, Section);
		}

		template <int32_t Group, int32_t Section>
		class ScopedBlock
		{
		public:
			ScopedBlock(const char* groupName, const char* sectionName)
			{
				Tracker::BeginBlock(Group, groupName, Section, sectionName);
			}
			~ScopedBlock()
			{
				Tracker::EndBlock(Group, Section);
			}
		};
	}
}

#define CPF_ENABLE_PERFORMANCE_TRACKING
#ifdef CPF_ENABLE_PERFORMANCE_TRACKING

#	define CPF_PERF_THREAD_NAME(name)

#	define CPF_PERF_BEGIN(group, section) CPF::Performance::BeginBlock<group##_crc32, section##_crc32>(group, section)
#	define CPF_PERF_END(group, section) CPF::Performance::EndBlock<group##_crc32, section##_crc32>()

#	define CPF_PERF_BLOCK(group, section) CPF::Performance::ScopedBlock<group##_crc32, section##_crc32> sPerformanceBlock##__line__(group, section)

#	define CPF_PERF_COUNTER_INC(name)
#	define CPF_PERF_COUNTER_DEC(name)

#	define CPF_PERF_FRAME_BEGIN
#	define CPF_PERF_FRAME_END

#else

#	define CPF_PERF_THREAD_NAME(name) {}
#	define CPF_PERF_BEGIN(group, section) {}
#	define CPF_PERF_END(group, section) {}
#	define CPF_PERF_BLOCK(group, section) {}
#	define CPF_PERF_COUNTER_INC(name) {}
#	define CPF_PERF_COUNTER_DEC(name) {}
#	define CPF_PERF_FRAME_BEGIN {}
#	define CPF_PERF_FRAME_END {}

#endif
