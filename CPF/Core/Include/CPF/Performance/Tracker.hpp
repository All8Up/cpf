//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Hash/Crc.hpp"
#include "CPF/Std/Vector.hpp"
#include <chrono>
#include <atomic>
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

			virtual void BeginFrame(Tick tick) = 0;
			virtual void EndFrame(Tick tick) = 0;

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

		void CPF_EXPORT BeginFrame();
		void CPF_EXPORT EndFrame();

		struct CounterData;
		void CPF_EXPORT AddCounter(CounterData* data);
		CounterData CPF_EXPORT * GetFirstCounter();

		void CPF_EXPORT Flush();

		//////////////////////////////////////////////////////////////////////////
		class CPF_EXPORT DefaultListener : public TrackerListener
		{
		public:
			virtual ~DefaultListener() = default;

			void SetInfo(Tick sinceEpoch, intmax_t numerator, intmax_t denominator) override;

			void ThreadNamed(size_t, const char*) override {}
			void IDMapped(int32_t id, const char* name) override;
			void BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;
			void EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick tick) override;

			void BeginFrame(Tick tick) override { mFrameBegin = tick; }
			void EndFrame(Tick tick) override { mFrameBegin = tick; }

			void Flush() override;

			//////////////////////////////////////////////////////////////////////////
			// Gathered information access.
			using TickRange = std::pair<Tick, Tick>;
			TickRange GetSampleRange() const { return TickRange{mFrameBegin, mFrameEnd}; }

		private:
			CPF_DLL_SAFE_BEGIN;
			std::mutex mMapLock;
			std::map<std::string, int32_t> mIDMap;
			CPF_DLL_SAFE_END;
			Tick mFrameBegin = 0;
			Tick mFrameEnd = 0;
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

		//////////////////////////////////////////////////////////////////////////
		enum class CounterType : int32_t
		{
			eFrameZeroed,
			eAverage10,
			eAverage100
		};

		struct CounterData
		{
			CounterType mType = CounterType::eFrameZeroed;
			std::atomic<int64_t> mValue;
			const char* mpName = nullptr;
			STD::Vector<int64_t> mHistory;
			size_t mHistoryIndex = 0;
			int64_t mAccumulator = 0;
			int64_t mAverage = 0;

			CounterData* mpNext = nullptr;
		};

		template <int32_t ID>
		struct CounterValue
		{
			static CounterData mData;
		};
		template <int32_t ID> CounterData CounterValue<ID>::mData;

		template <int32_t ID>
		void CounterCreate(CounterType type, const char* name)
		{
			CounterValue<ID>::mData.mType = type;
			CounterValue<ID>::mData.mValue.store(0);
			CounterValue<ID>::mData.mpName = name;
			AddCounter(&CounterValue<ID>::mData);
		}
	}
}

#define CPF_ENABLE_PERFORMANCE_TRACKING
#ifdef CPF_ENABLE_PERFORMANCE_TRACKING

//////////////////////////////////////////////////////////////////////////
#	define CPF_PERF_THREAD_NAME(name) CPF::Performance::SetThreadName(name)

#	define CPF_PERF_BEGIN(group, section) CPF::Performance::BeginBlock<group##_crc32, section##_crc32>(group, section)
#	define CPF_PERF_END(group, section) CPF::Performance::EndBlock<group##_crc32, section##_crc32>()

#	define CPF_PERF_BLOCK(group, section) CPF::Performance::ScopedBlock<group##_crc32, section##_crc32> sPerformanceBlock##__COUNTER__(group, section)

#	define CPF_PERF_COUNTER(name) CPF::Performance::CounterValue<name##_crc32>
#	define CPF_PERF_COUNTER_GET(name) CPF_PERF_COUNTER(name)::mData.mValue
#	define CPF_PERF_COUNTER_GET_AVG(name) CPF_PERF_COUNTER(name)::mData.mAverage
#	define CPF_PERF_COUNTER_CREATE(name, type) CPF::Performance::CounterCreate<name##_crc32>(type, name)
#	define CPF_PERF_COUNTER_SET(name, val) CPF_PERF_COUNTER(name)::mData.mValue.store(val)
#	define CPF_PERF_COUNTER_INC(name) CPF_PERF_COUNTER(name)::mData.mValue.fetch_add(1)
#	define CPF_PERF_COUNTER_ADD(name, val) CPF_PERF_COUNTER(name)::mData.mValue.fetch_add(val)
#	define CPF_PERF_COUNTER_DEC(name) CPF_PERF_COUNTER(name)::mData.mValue.fetch_sub(1)
#	define CPF_PERF_COUNTER_SUB(name, val) CPF_PERF_COUNTER(name)::mData.mValue.fetch_sub(val)

#	define CPF_PERF_FRAME_BEGIN() CPF::Performance::BeginFrame()
#	define CPF_PERF_FRAME_END() CPF::Performance::EndFrame()

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
