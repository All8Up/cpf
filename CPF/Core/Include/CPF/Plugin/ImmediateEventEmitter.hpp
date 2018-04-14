//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/GOM/iEventEmitter.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/UnorderedMap.hpp"

namespace CPF
{
	namespace Plugin
	{
		class ImmediateEventEmitter
		{
		public:
			GOM::Result OnEvent(int64_t id, GOM::EventHandler cb, void* context);
			GOM::Result RemoveEvent(int64_t id, GOM::EventHandler cb, void* context);
			GOM::Result EmitEvent(int64_t id, size_t eventSize, const void* eventData) const;

			template <typename EVENT_TYPE>
			GOM::Result Emit(const EVENT_TYPE* eventStruct) const;

		private:
			struct EventHandler
			{
				GOM::EventHandler mpHandler;
				void* mpContext;
			};
			using EventHandlers = STD::Vector<EventHandler>;
			STD::UnorderedMap<int64_t, EventHandlers> mEventMap;
		};

		inline GOM::Result ImmediateEventEmitter::OnEvent(int64_t id, GOM::EventHandler cb, void* context)
		{
			auto handlerList = mEventMap.find(id);
			if (handlerList == mEventMap.end())
			{
				mEventMap.insert({ id, EventHandlers() });
				handlerList = mEventMap.find(id);
			}
#ifdef CPF_DEBUG
			// Check for duplication.
			for (const auto& handler : handlerList->second)
			{
				CPF_ASSERT(handler.mpHandler != cb || handler.mpContext != context);
			}
#endif
			handlerList->second.push_back({ cb, context });

			return GOM::kOK;
		}

		inline GOM::Result ImmediateEventEmitter::RemoveEvent(int64_t id, GOM::EventHandler cb, void* context)
		{
			auto handlerList = mEventMap.find(id);
			if (handlerList == mEventMap.end())
				return GOM::kNotFound;
			for (auto ibegin = handlerList->second.begin(), iend = handlerList->second.end(); ibegin != iend; ++ibegin)
			{
				if (ibegin->mpHandler == cb && ibegin->mpContext == context)
				{
					handlerList->second.erase(ibegin);
					return GOM::kOK;
				}
			}
			return GOM::kNotFound;
		}

		inline GOM::Result ImmediateEventEmitter::EmitEvent(int64_t id, size_t eventSize, const void* eventData) const
		{
			(void)eventSize; // Not needed in non-deferred event systems.
			auto handlerList = mEventMap.find(id);
			if (handlerList == mEventMap.end())
				return GOM::kNotFound;
			for (const auto& ev : handlerList->second)
			{
				(*ev.mpHandler)(ev.mpContext, eventData);
			}
			return GOM::kOK;
		}

		template <typename EVENT_TYPE>
		GOM::Result ImmediateEventEmitter::Emit(const EVENT_TYPE* eventStruct) const
		{
			return EmitEvent(EVENT_TYPE::kID, sizeof(EVENT_TYPE), eventStruct);
		}
	}
}
