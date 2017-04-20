//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Events/Events.hpp"
#include "Events/Id.hpp"
#include "Events/Event.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Events
	{
		/*
		I'd like to modify these to use a single template for the emitter
		where you select the queue behavior via template.  Then I can
		expand the deferred solution to be a gather scatter system for
		threading systems more easily.  I.e
		using Emitter = Emitter<Immediate>;
		using DeferredEmitter = Emitter<DeferredQueue>;
		using SGEmitter = Emitter<SGQueue>;
		*/

		/** @brief Base class for emitters. */
		class EmitterBase
		{
		public:
			//
			EmitterBase();
			virtual ~EmitterBase();

			//
			void Enable();
			bool Enabled() const;
			void Disable();

			//
			template<typename EVENTTYPE>
			HandleBase On(typename EVENTTYPE::FunctionDecl_t func);
			void Remove(HandleBase& evh);

		protected:
			//
			using EventMap_t = UnorderedMap<size_t, EventBase*>;
			using IdPairVector_t = Vector<std::pair<Id_t, Id_t>>;
			using VoidFunction_t = std::function<void(void)>;
			using AddVector_t = Vector<VoidFunction_t>;

			//
			void _Remove(Id_t, Id_t);
			void _DoRemoves();
			void _Add(std::function<void(void)>);
			void _DoAdds();
			Id_t _GetNextId();

			//
			EventMap_t mEventMap;
			bool mEmitting;

		private:
			bool mEnabled;
			Id_t mCurrentId;
			AddVector_t mAdds;
			IdPairVector_t mRemoves;
		};


		/**
		 * @brief Implementation of immediate dispatch emitter.
		 */
		class Emitter : public EmitterBase
		{
		public:
			//
			Emitter();
			virtual ~Emitter();

			//
			template<typename EVENTTYPE, typename... ARGS>
			typename EVENTTYPE::ResultType_t Emit(ARGS...);
		};


		/** @brief Implementation of an emitter which queues emissions for later application. */
		class DeferredEmitter : public EmitterBase
		{
		public:
			//
			DeferredEmitter();
			~DeferredEmitter();

			//
			void operator ()();

			//
			template<typename EVENTTYPE, typename... ARGS>
			void Post(ARGS...);
			template<typename EVENTTYPE, typename... ARGS>
			void Emit(typename EVENTTYPE::HandlerType_t handler, ARGS...);

		private:
			AddVector_t mQueue;
		};
	}
}

#include "Events/Handle.hpp"


namespace Cpf
{
	namespace Events
	{
		//////////////////////////////////////////////////////////////////////////
		/// Constructor
		//////////////////////////////////////////////////////////////////////////
		inline EmitterBase::EmitterBase()
			: mEmitting(false)
			, mEnabled(true)
			, mCurrentId(0)
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Destructor
		//////////////////////////////////////////////////////////////////////////
		inline EmitterBase::~EmitterBase()
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Enable the event emitter.
		//////////////////////////////////////////////////////////////////////////
		inline void EmitterBase::Enable()
		{
			mEnabled = true;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Determine if the emitter is enabled or ignoring emit calls.
		/// @result true if the emitter is enabled, false otherwise.
		//////////////////////////////////////////////////////////////////////////
		inline bool EmitterBase::Enabled() const
		{
			return mEnabled;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Disable the event emitter.
		//////////////////////////////////////////////////////////////////////////
		inline void EmitterBase::Disable()
		{
			mEnabled = false;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Remove an event handler.
		//////////////////////////////////////////////////////////////////////////
		inline void EmitterBase::Remove(HandleBase& evh)
		{
			if (mEmitting)
				mRemoves.push_back(std::pair<Id_t, Id_t>(evh.EventId(), evh.BindingId()));
			else
				_Remove(evh.EventId(), evh.BindingId());
		}


		/**
		 * @brief Removes the specified event handler.
		 * @param eId The identifier of the event type.
		 * @param bId The identifier of the specific binding.
		 */
		inline void EmitterBase::_Remove(Id_t eId, Id_t bId)
		{
			EventMap_t::iterator it = mEventMap.find(eId);
			if (it != mEventMap.end())
				it->second->Remove(bId);
		}


		/** @brief Removes the queued up items. */
		inline void EmitterBase::_DoRemoves()
		{
			for (auto f : mRemoves)
				_Remove(f.first, f.second);
			mRemoves.clear();
		}


		/**
		 * @brief Adds a function to be called in the adds step.  Generally this would add a new handler.
		 * @param f The function that does the actual work.
		 */
		inline void EmitterBase::_Add(std::function<void(void)> f)
		{
			mAdds.push_back(f);
		}


		/** @brief Processes the adds list, calling each item and then clearing for the next loop. */
		inline void EmitterBase::_DoAdds()
		{
			for (auto f : mAdds)
				f();
			mAdds.clear();
		}

		/**
		 * @brief Gets the next identifier.
		 * @return The next identifier.
		 */
		inline Id_t EmitterBase::_GetNextId()
		{
			// TODO: Make m_currentId atomic for thread safety.
			return ++mCurrentId;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Bind a handler to a given event.
		/// @tparam EVENTTYPE The typedef of the event which this handler
		/// will be bound to.
		/// @param func The handler function to bind to the event.
		//////////////////////////////////////////////////////////////////////////
		template<typename EVENTTYPE>
		HandleBase EmitterBase::On(typename EVENTTYPE::FunctionDecl_t func)
		{
			Id_t theId = _GetNextId();

			auto addEvent = [=]() {
				auto it = mEventMap.find(EVENTTYPE::Id());
				if (it == mEventMap.end())
				{
					mEventMap[EVENTTYPE::Id()] = new EVENTTYPE();
					it = mEventMap.find(EVENTTYPE::Id());
				}

				typename EVENTTYPE::EventType_t* evt = reinterpret_cast<typename EVENTTYPE::EventType_t*>(it->second);
				evt->FunctionMap()[theId] = func;
			};

			if (mEmitting)
			{
				mAdds.push_back(addEvent);
			}
			else
			{
				addEvent();
			}
			return HandleBase(this, EVENTTYPE::Id(), mCurrentId);
		}


		//////////////////////////////////////////////////////////////////////////
		/// Emit an event to all bound handlers.
		/// @tparam EVENTTYPE The typedef of the event to emit.
		/// @param args The arguments passed to the event handlers.
		//////////////////////////////////////////////////////////////////////////
		template<typename EVENTTYPE, typename... ARGS>
		typename EVENTTYPE::ResultType_t Emitter::Emit(ARGS... args)
		{
			using IntegratorType_t = typename EVENTTYPE::IntegratorType_t;

			// If not enabled or already emitting, don't fire again.
			// The assertion is intended to prevent chains.
			CPF_ASSERT(mEmitting == false);

			// Chains of emissions can actually be done in an asynchronous
			// version of this system but can't be done here due to the calling
			// convention of having a return type.
			IntegratorType_t integrator;
			if (!Enabled() || mEmitting)
				return integrator();

			EventMap_t::const_iterator it = mEventMap.find(EVENTTYPE::Id());
			if (it != mEventMap.end())
			{
				mEmitting = true;

				const typename EVENTTYPE::EventType_t* evt = reinterpret_cast<const typename EVENTTYPE::EventType_t*>(it->second);

				// Execute all the handlers.
				for (auto f : evt->FunctionMap())
					integrator(f.second, args...);

				_DoAdds();
				_DoRemoves();

				mEmitting = false;
			}

			return integrator();
		}


		//////////////////////////////////////////////////////////////////////////
		/// Constructor
		//////////////////////////////////////////////////////////////////////////
		inline Emitter::Emitter()
			: EmitterBase()
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Destructor
		//////////////////////////////////////////////////////////////////////////
		inline Emitter::~Emitter()
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Constructor
		//////////////////////////////////////////////////////////////////////////
		inline DeferredEmitter::DeferredEmitter()
			: EmitterBase()
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Destructor
		//////////////////////////////////////////////////////////////////////////
		inline DeferredEmitter::~DeferredEmitter()
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Dispatch the waiting events.
		//////////////////////////////////////////////////////////////////////////
		inline void DeferredEmitter::operator ()()
		{
			for (auto it : mQueue)
			{
				it();
			}
			mQueue.clear();
		}

		/**
		 * @brief Encapsulates the result of an apply, dealing with void types.
		 * @tparam RESULT Type of the result.
		 */
		template<typename HANDLER, typename INTEGRATOR, typename RESTYPE>
		struct ApplyResult
		{
			static void Apply(HANDLER handler, INTEGRATOR& res) { handler(res()); }
		};
		template<typename HANDLER, typename INTEGRATOR>
		struct ApplyResult<HANDLER, INTEGRATOR, void>
		{
			static void Apply(HANDLER handler, INTEGRATOR&) { handler(); }
		};


		//////////////////////////////////////////////////////////////////////////
		template<typename EVENTTYPE, typename... ARGS>
		void DeferredEmitter::Post(ARGS... args)
		{
			// If not enabled or already emitting, don't fire again.
			// The assertion is intended to prevent chains.
			CPF_ASSERT(mEmitting == false);

			// Chains of emissions can actually be done, but should they?
			if (!Enabled() || mEmitting)
			{
				return;
			}

			mQueue.push_back([=]() {
				EventMap_t::const_iterator it = mEventMap.find(EVENTTYPE::Id());
				if (it != mEventMap.end())
				{
					mEmitting = true;

					const typename EVENTTYPE::EventType_t* evt = reinterpret_cast<const typename EVENTTYPE::EventType_t*>(it->second);

					// Execute all the handlers.
					for (auto f : evt->FunctionMap())
						f.second(args...);

					_DoAdds();
					_DoRemoves();

					mEmitting = false;
				}
			});
		}


		//////////////////////////////////////////////////////////////////////////
		/// Emit an event to all bound handlers.
		/// @tparam EVENTTYPE The typedef of the event to emit.
		/// @param args The arguments passed to the event handlers.
		//////////////////////////////////////////////////////////////////////////
		template<typename EVENTTYPE, typename... ARGS>
		void DeferredEmitter::Emit(typename EVENTTYPE::HandlerType_t handler, ARGS... args)
		{
			using IntegratorType_t = typename EVENTTYPE::IntegratorType_t;

			// If not enabled or already emitting, don't fire again.
			// The assertion is intended to prevent chains.
			CPF_ASSERT(mEmitting == false);

			IntegratorType_t integrator;
			if (!Enabled() || mEmitting)
			{
				ApplyResult<typename EVENTTYPE::HandlerType_t, IntegratorType_t, typename IntegratorType_t::ResultType_t>::Apply(handler, integrator);
				return;
			}

			mQueue.push_back([=]() {
				EventMap_t::const_iterator it = mEventMap.find(EVENTTYPE::Id());
				if (it != mEventMap.end())
				{
					mEmitting = true;

					const typename EVENTTYPE::EventType_t* evt = reinterpret_cast<const typename EVENTTYPE::EventType_t*>(it->second);

					// Execute all the handlers.
					IntegratorType_t integrator;
					for (auto f : evt->FunctionMap())
						integrator(f.second, args...);

					_DoAdds();
					_DoRemoves();

					mEmitting = false;

					ApplyResult<typename EVENTTYPE::HandlerType_t, IntegratorType_t, typename IntegratorType_t::ResultType_t>::Apply(handler, integrator);
				}
			});
		}
	}
}
