//////////////////////////////////////////////////////////////////////////
#include "CPF/Performance/Tracker.hpp"
#include "CPF/Performance/Internal/blockingconcurrentqueue.h"
#include "CPF/Logging.hpp"
#include <thread>

using namespace moodycamel;

namespace CPF
{
	namespace Performance
	{
		//////////////////////////////////////////////////////////////////////////
		using EventFunction = std::function<void(TrackerListener*)>;
		Vector<TrackerListener*> sListeners;
		BlockingConcurrentQueue<EventFunction> sEventQueue;
		std::thread sEventThread;

		void EventWorker()
		{
			for (;;)
			{
				EventFunction func;
				sEventQueue.wait_dequeue(func);
				if (func)
				{
					for (const auto& listener : sListeners)
					{
						func(listener);
					}
				}
				else
					break;
			}
		}

		void InstallListener(TrackerListener* listener)
		{
			sListeners.push_back(listener);
		}

		void Initialize()
		{
			// Send startup information to the listeners.  While this is mostly
			// irrelevant for something running on the local machine but important
			// if the data is logged to file, sent over the network to another
			// machine etc.
			sEventThread = std::thread(&EventWorker);
			sEventQueue.enqueue([](TrackerListener* listener)
			{
				listener->SetInfo(
					PerformanceClock::now().time_since_epoch().count(),
					PerformanceClock::period::num,
					PerformanceClock::period::den
				);
			});
		}

		void Shutdown()
		{
			sEventQueue.enqueue(EventFunction());
			sEventThread.join();
			for (const auto& listener : sListeners)
				delete listener;
			sListeners.clear();
		}

		void MapID(int32_t id, const char* name)
		{
			sEventQueue.enqueue([=](TrackerListener* listener)
			{
				listener->IDMapped(id, name);
			});
		}

		void BeginBlock(int32_t group, int32_t section)
		{
			const auto ticks = PerformanceClock::now().time_since_epoch().count();
			const std::hash<std::thread::id> hasher;
			const size_t threadID = hasher(std::this_thread::get_id());
			sEventQueue.enqueue([=](TrackerListener* listener)
			{
				listener->BeginBlock(threadID, group, section, ticks);
			});
		}

		void EndBlock(int32_t group, int32_t section)
		{
			const auto ticks = PerformanceClock::now().time_since_epoch().count();
			const std::hash<std::thread::id> hasher;
			const size_t threadID = hasher(std::this_thread::get_id());
			sEventQueue.enqueue([=](TrackerListener* listener)
			{
				listener->EndBlock(threadID, group, section, ticks);
			});
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
