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

			virtual void ThreadNamed(size_t threadID, const char* name) = 0;
			virtual void IDMapped(int32_t id, const char* name) = 0;

			virtual void BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) = 0;
			virtual void EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) = 0;

			virtual void BeginFrame(int32_t id, Tick tick) = 0;
			virtual void EndFrame(int32_t id, Tick tick) = 0;

			virtual void Flush() = 0;
		};

		//////////////////////////////////////////////////////////////////////////
		void CPF_EXPORT InstallListener(TrackerListener* listener);

		void CPF_EXPORT Initialize();
		void CPF_EXPORT Shutdown();

		void CPF_EXPORT MapID(int32_t id, const char* name);

		void CPF_EXPORT SetThreadName(size_t id, const char* name);

		void CPF_EXPORT BeginBlock(int32_t group, int32_t section);
		void CPF_EXPORT EndBlock(int32_t group, int32_t section);

		void CPF_EXPORT BeginFrame(int32_t name);
		void CPF_EXPORT EndFrame(int32_t name);

		void CPF_EXPORT Flush();

		//////////////////////////////////////////////////////////////////////////
		class CPF_EXPORT DefaultListener : public TrackerListener
		{
		public:
			virtual ~DefaultListener() = default;

			void SetInfo(Tick sinceEpoch, intmax_t numerator, intmax_t denominator) override;

			void ThreadNamed(size_t threadID, const char* name) override {}
			void IDMapped(int32_t id, const char* name) override;
			void BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;
			void EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;

			void BeginFrame(int32_t, Tick) override {}
			void EndFrame(int32_t, Tick) override {}

			void Flush() override;

			//////////////////////////////////////////////////////////////////////////
			// Data access.
			using TickRange = std::pair<Tick, Tick>;
			TickRange GetSampleRange() const { return TickRange{0, 0}; }

		private:
			CPF_DLL_SAFE_BEGIN;
			std::mutex mMapLock;
			std::map<std::string, int32_t> mIDMap;
			CPF_DLL_SAFE_END;
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
				initialized = true;
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

		//////////////////////////////////////////////////////////////////////////
		template <int32_t Name>
		void FrameBegin(const char* name)
		{
			static bool initialized = false;
			if (!initialized)
			{
				MapID(Name, name);
				initialized = true;
			}
			BeginFrame(Name);
		}
		template <int32_t Name>
		void FrameEnd()
		{
			EndFrame(Name);
		}

		//////////////////////////////////////////////////////////////////////////
		inline void SetThreadName(const char* name)
		{
			static bool initialized = false;
			if (!initialized)
			{
				const std::hash<std::thread::id> hasher;
				const size_t threadID = hasher(std::this_thread::get_id());
				SetThreadName(threadID, name);
				initialized = true;
			}
		}
	}
}

#define CPF_ENABLE_PERFORMANCE_TRACKING
#ifdef CPF_ENABLE_PERFORMANCE_TRACKING

//////////////////////////////////////////////////////////////////////////
#	define CPF_PERF_THREAD_NAME(name) CPF::Performance::SetThreadName(name)

#	define CPF_PERF_BEGIN(group, section) CPF::Performance::BeginBlock<group##_crc32, section##_crc32>(group, section)
#	define CPF_PERF_END(group, section) CPF::Performance::EndBlock<group##_crc32, section##_crc32>()

#	define CPF_PERF_BLOCK(group, section) CPF::Performance::ScopedBlock<group##_crc32, section##_crc32> sPerformanceBlock##__line__(group, section)

#	define CPF_PERF_COUNTER_INIT(name, type) CPF::Performance::CounterInit<name##_crc32>(type)
#	define CPF_PERF_COUNTER_SET(name, val) CPF::Performance::CounterSet<name##_crc32>(val);
#	define CPF_PERF_COUNTER_INC(name) CPF::Performance::CounterInc<name##_crc32>()
#	define CPF_PERF_COUNTER_ADD(name, val) CPF::Performance::CounterAdd<name##_crc32>()
#	define CPF_PERF_COUNTER_DEC(name) CPF::Performance::CounterDec<name##_crc32>()
#	define CPF_PERF_COUNTER_SUB(name, val) CPF::Performance::CounterSub<name##_crc32>()
#	define CPF_PERF_COUNTER_MIN(name, val) CPF::Performance::CounterMin<name##_crc32>()
#	define CPF_PERF_COUNTER_MAX(name, val) CPF::Performance::CounterMax<name##_crc32>()

#	define CPF_PERF_FRAME_BEGIN(name) CPF::Performance::FrameBegin<name##_crc32>(name)
#	define CPF_PERF_FRAME_END(name) CPF::Performance::FrameEnd<name##_crc32>()

#	define CPF_PERF_FLUSH CPF::Performance::Flush()

#else

//////////////////////////////////////////////////////////////////////////
#	define CPF_PERF_THREAD_NAME(name) {}
#	define CPF_PERF_BEGIN(group, section) {}
#	define CPF_PERF_END(group, section) {}
#	define CPF_PERF_BLOCK(group, section) {}
#	define CPF_PERF_COUNTER_INC(name) {}
#	define CPF_PERF_COUNTER_DEC(name) {}
#	define CPF_PERF_FRAME_BEGIN(name) {}
#	define CPF_PERF_FRAME_END(name) {}

#endif
