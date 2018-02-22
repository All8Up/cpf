//////////////////////////////////////////////////////////////////////////
#include "CPF/Performance/Tracker.hpp"
#include "CPF/Logging.hpp"
#include <thread>

namespace CPF
{
	namespace Performance
	{
		//////////////////////////////////////////////////////////////////////////
		Vector<TrackerListener*> mListeners;


		void InstallListener(TrackerListener* listener)
		{
			mListeners.push_back(listener);
		}

		void Initialize()
		{
			// Send startup information to the listeners.  While this is mostly
			// irrelevant for something running on the local machine but important
			// if the data is logged to file, sent over the network to another
			// machine etc.
			for (const auto& listener : mListeners)
			{
				listener->SetInfo(
					PerformanceClock::now().time_since_epoch().count(),
					PerformanceClock::period::num,
					PerformanceClock::period::den
				);
			}
		}

		void MapID(int32_t id, const char* name)
		{
			for (const auto& listener : mListeners)
				listener->IDMapped(id, name);
		}

		void BeginBlock(int32_t group, int32_t section)
		{
			const auto ticks = PerformanceClock::now().time_since_epoch().count();
			const std::hash<std::thread::id> hasher;
			const size_t threadID = hasher(std::this_thread::get_id());
			for (const auto& listener : mListeners)
			{
				listener->BeginBlock(threadID, group, section, ticks);
			}
		}

		void EndBlock(int32_t group, int32_t section)
		{
			const auto ticks = PerformanceClock::now().time_since_epoch().count();
			const std::hash<std::thread::id> hasher;
			const size_t threadID = hasher(std::this_thread::get_id());
			for (const auto& listener : mListeners)
			{
				listener->EndBlock(threadID, group, section, ticks);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
using namespace CPF;
using namespace Performance;

void DefaultListener::SetInfo(Tick sinceEpoch, intmax_t numerator, intmax_t denominator)
{
	CPF_LOG(TimeTracker, Info) << "Start ticks: " << sinceEpoch << std::endl;
	CPF_LOG(TimeTracker, Info) << " Tick ratio: " << numerator << " / " << denominator << std::endl;
}

void DefaultListener::IDMapped(int32_t id, const char* name)
{
	std::lock_guard<std::mutex> lock(mMapLock);
	const auto it = mIDMap.find(std::string(name));
	if (it != mIDMap.end())
		return;
	mIDMap[std::string(name)] = id;
}

void DefaultListener::BeginBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick ticks)
{
}

void DefaultListener::EndBlock(size_t threadID, int32_t groupID, int32_t sectionID, Tick ticks)
{
}
