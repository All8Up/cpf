//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Events/Events.hpp"
#include "Events/Id.hpp"
#include "Events/Integrators.hpp"
#include "UnorderedMap.hpp"
#include "Functional.hpp"

namespace CPF
{
	namespace Events
	{
		/**
		 * @brief Handler selector for non-void result types.
		 * @tparam RESULTTYPE Non-void result type.
		 */
		template<typename RESULTTYPE>
		struct HandlerSelect
		{
			typedef Function<void(RESULTTYPE)> HandlerType_t;
		};


		/** @brief A handler selector to special case void result types. */
		template<>
		struct HandlerSelect<void>
		{
			typedef Function<void()> HandlerType_t;
		};


		/** @brief The untyped event base class. */
		class EventBase
		{
		public:
			virtual ~EventBase() = 0;
			virtual void Remove(Id_t) = 0;
		};

		inline EventBase::~EventBase() {}


		/**
		 * @brief The typed event class.  Supplies enough information for a type
		 * 		  (mostly) safe interface into the event handling.
		 * @tparam ID A unique identifier for the event type.
		 * @tparam FUNCDECL The function declaration of the bound handler.
		 * @tparam INTEGRATOR A primitive ability to have handler results with
		 * 					  multiple bound handlers.
		 */
		template< const int64_t ID, typename FUNCDECL, typename INTEGRATOR = Integrators::LastOf<typename FUNCDECL::result_type> >
		class Event : public EventBase
		{
		public:
			static Id_t Id();
			typedef typename FUNCDECL::result_type ResultType_t;
			typedef typename HandlerSelect<typename FUNCDECL::result_type>::HandlerType_t HandlerType_t;
			typedef INTEGRATOR IntegratorType_t;
			typedef FUNCDECL FunctionDecl_t;
			typedef UnorderedMap<Id_t, FunctionDecl_t> FunctionMap_t;
			typedef Event<ID, FUNCDECL, INTEGRATOR> EventType_t;

			void Remove(Id_t id) override;

			FunctionMap_t& FunctionMap();
			FunctionMap_t const& FunctionMap() const;

		private:
			FunctionMap_t m_bindings;
		};

		/**
		 * @brief Gets the identifier of the specific event.
		 * @tparam ID The event id of the handler type.
		 * @tparam FUNCDECL The callback function declaration.
		 * @tparam TEGRATOR The integrator used on return types.
		 * @return A Id_t.
		 */
		template< const int64_t ID, typename FUNCDECL, typename INTEGRATOR >
		Id_t Event<ID, FUNCDECL, INTEGRATOR>::Id()
		{
			return ID;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Remove a bound event from the emitter.
		//////////////////////////////////////////////////////////////////////////
		template< const int64_t ID, typename FUNCDECL, typename INTEGRATOR >
		inline void Event<ID, FUNCDECL, INTEGRATOR>::Remove(Id_t id)
		{
			typename FunctionMap_t::const_iterator it = m_bindings.find(id);
			if (it != m_bindings.end())
				m_bindings.erase(it);
		}


		//////////////////////////////////////////////////////////////////////////
		/// Get the function map for the event type.
		//////////////////////////////////////////////////////////////////////////
		template< const int64_t ID, typename FUNCDECL, typename INTEGRATOR >
		typename Event<ID, FUNCDECL, INTEGRATOR>::FunctionMap_t& Event<ID, FUNCDECL, INTEGRATOR>::FunctionMap()
		{
			return m_bindings;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Get the function map for the event type.
		//////////////////////////////////////////////////////////////////////////
		template< const int64_t ID, typename FUNCDECL, typename INTEGRATOR >
		typename Event<ID, FUNCDECL, INTEGRATOR>::FunctionMap_t const& Event<ID, FUNCDECL, INTEGRATOR>::FunctionMap() const
		{
			return m_bindings;
		}
	}
}
