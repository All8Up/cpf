//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Hash/Crc.hpp"
#include "CPF/Std/Vector.hpp"
#include <chrono>
#include <mutex>
#include <map>

namespace CPF
{
	namespace Performance
	{
		using PerformanceClock = std::chrono::high_resolution_clock;
		using TimePoint = PerformanceClock::time_point;
		using Duration = PerformanceClock::duration;
		using Tick = Duration::rep;

		//////////////////////////////////////////////////////////////////////////
		struct TrackerListener
		{
			virtual ~TrackerListener() = 0 {}

			virtual void SetInfo(Tick sinceEpoch, intmax_t numerator, intmax_t denominator) = 0;

			virtual void IDMapped(int32_t id, const char* name) = 0;

			virtual void BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) = 0;
			virtual void EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		void CPF_EXPORT InstallListener(TrackerListener* listener);

		void CPF_EXPORT Initialize();
		void CPF_EXPORT MapID(int32_t id, const char* name);
		void CPF_EXPORT BeginBlock(int32_t group, int32_t section);
		void CPF_EXPORT EndBlock(int32_t group, int32_t section);

		//////////////////////////////////////////////////////////////////////////
		class DefaultListener : TrackerListener
		{
		public:
			virtual ~DefaultListener() = default;

			void SetInfo(Tick sinceEpoch, intmax_t numerator, intmax_t denominator) override;

			void IDMapped(int32_t id, const char* name) override;
			void BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;
			void EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;

		private:
			std::mutex mMapLock;
			std::map<std::string, int32_t> mIDMap;
		};

		//////////////////////////////////////////////////////////////////////////
		template <int32_t Group, int32_t Section>
		void BeginBlock(const char* groupName, const char* sectionName)
		{
			static bool initialized = false;
			if (!initialized)
			{
				MapID(Group, groupName);
				MapID(Section, sectionName);
			}
			BeginBlock(Group, Section);
		}

		//////////////////////////////////////////////////////////////////////////
		template <int32_t Group, int32_t Section>
		void EndBlock()
		{
			EndBlock(Group, Section);
		}

		//////////////////////////////////////////////////////////////////////////
		template <int32_t Group, int32_t Section>
		class ScopedBlock
		{
		public:
			ScopedBlock(const char* groupName, const char* sectionName)
			{
				BeginBlock<Group, Section>(groupName, sectionName);
			}
			~ScopedBlock()
			{
				EndBlock<Group, Section>();
			}
		};
	}
}

#define CPF_ENABLE_PERFORMANCE_TRACKING
#ifdef CPF_ENABLE_PERFORMANCE_TRACKING

//////////////////////////////////////////////////////////////////////////
#	define CPF_PERF_THREAD_NAME(name)

#	define CPF_PERF_BEGIN(group, section) CPF::Performance::BeginBlock<group##_crc32, section##_crc32>(group, section)
#	define CPF_PERF_END(group, section) CPF::Performance::EndBlock<group##_crc32, section##_crc32>()

#	define CPF_PERF_BLOCK(group, section) CPF::Performance::ScopedBlock<group##_crc32, section##_crc32> sPerformanceBlock##__line__(group, section)

#	define CPF_PERF_COUNTER_INC(name)
#	define CPF_PERF_COUNTER_DEC(name)

#	define CPF_PERF_FRAME_BEGIN
#	define CPF_PERF_FRAME_END

#else

//////////////////////////////////////////////////////////////////////////
#	define CPF_PERF_THREAD_NAME(name) {}
#	define CPF_PERF_BEGIN(group, section) {}
#	define CPF_PERF_END(group, section) {}
#	define CPF_PERF_BLOCK(group, section) {}
#	define CPF_PERF_COUNTER_INC(name) {}
#	define CPF_PERF_COUNTER_DEC(name) {}
#	define CPF_PERF_FRAME_BEGIN {}
#	define CPF_PERF_FRAME_END {}

#endif
