//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/GOM/iEventEmitter.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/UnorderedMap.hpp"
#include "CPF/IntrusivePtr.hpp"

namespace CPF
{
	namespace Plugin
	{
		class ImmediateEventEmitter
		{
		public:
            ImmediateEventEmitter();

			GOM::Result OnEvent(int64_t id, GOM::EventHandler cb, void* context);
			GOM::Result RemoveEvent(int64_t id, GOM::EventHandler cb, void* context);
			GOM::Result EmitEvent(int64_t id, size_t eventSize, const void* eventData) const;
            GOM::Result SetEventSink(GOM::iEventSink*);

			template <typename EVENT_TYPE>
			GOM::Result Emit(const EVENT_TYPE* eventStruct) const;

		private:
            struct ImmediateSink : GOM::iEventSink
            {
                virtual ~ImmediateSink() = default;

                virtual int32_t CPF_STDCALL AddRef() { return 1; }
                virtual int32_t CPF_STDCALL Release() { return 1; }
                virtual GOM::Result CPF_STDCALL QueryInterface(GOM::IID, void**) { return GOM::kNotImplemented; }

                GOM::Result CPF_STDCALL Post(GOM::EventHandler handler, size_t, const void* eventData, void* context) override
                {
                    (*handler)(context, eventData);
                    return GOM::kOK;
                }
            };

			struct EventHandler
			{
				GOM::EventHandler mpHandler;
				void* mpContext;
			};
			using EventHandlers = STD::Vector<EventHandler>;
			STD::UnorderedMap<int64_t, EventHandlers> mEventMap;
            ImmediateSink mSink;
            IntrusivePtr<GOM::iEventSink> mpSink;
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

        inline ImmediateEventEmitter::ImmediateEventEmitter()
        {
            mpSink = IntrusivePtr<GOM::iEventSink>(&mSink);
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
                mpSink->Post(ev.mpHandler, eventSize, eventData, ev.mpContext);
			}
			return GOM::kOK;
		}

        inline GOM::Result ImmediateEventEmitter::SetEventSink(GOM::iEventSink* sink)
        {
            if (sink == nullptr)
                mpSink = IntrusivePtr<GOM::iEventSink>(&mSink);
            else
                mpSink = TakeIntrusivePtr(sink);
            return GOM::kOK;
        }

		template <typename EVENT_TYPE>
		GOM::Result ImmediateEventEmitter::Emit(const EVENT_TYPE* eventStruct) const
		{
			return EmitEvent(EVENT_TYPE::kID, sizeof(EVENT_TYPE), eventStruct);
		}
	}
}
