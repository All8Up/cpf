//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Event/Id.hpp"

namespace CPF
{
	namespace Events
	{
		class EmitterBase;

		//////////////////////////////////////////////////////////////////////////
		/// Basic handle to a bound event.  Does not own the event and will not
		/// automatically remove it when this handle goes out of scope.
		//////////////////////////////////////////////////////////////////////////
		class HandleBase
		{
		public:
			//
			HandleBase(EmitterBase* emitter, Id_t eventId, Id_t bindingId);
			HandleBase(HandleBase&& rhs) noexcept;

			//
			HandleBase& operator =(HandleBase&&) noexcept;
			bool operator ==(const HandleBase&) const;

			//
			EmitterBase* Emitter() const;
			Id_t EventId() const;
			Id_t BindingId() const;

			//
			void Abandon();

		protected:
			HandleBase() = delete;
			HandleBase(const HandleBase& rhs) = delete;
			HandleBase& operator =(const HandleBase&) = delete;

			EmitterBase* m_pEmitter;
			Id_t m_eventId;
			Id_t m_bindingId;
		};


		//////////////////////////////////////////////////////////////////////////
		/// Handle to an event which will automatically remove the event when the
		/// handle goes out of scope.
		//////////////////////////////////////////////////////////////////////////
		class Handle : public HandleBase
		{
		public:
			Handle(EmitterBase* emitter, Id_t eventId, Id_t bindingId);
			Handle(Handle&& rhs) noexcept;
			explicit Handle(HandleBase&& rhs) noexcept;

			~Handle();

			Handle& operator = (Handle&& rhs) noexcept;
			bool operator ==(const Handle&) const;

		private:
			Handle() = delete;
			Handle(const Handle&) = delete;
			Handle& operator =(const Handle&) = delete;
		};

		//////////////////////////////////////////////////////////////////////////
		/// Constructor
		//////////////////////////////////////////////////////////////////////////
		inline HandleBase::HandleBase(EmitterBase* emitter, Id_t eventId, Id_t bindingId)
			: m_pEmitter(emitter)
			, m_eventId(eventId)
			, m_bindingId(bindingId)
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Move constructor
		//////////////////////////////////////////////////////////////////////////
		inline HandleBase::HandleBase(HandleBase&& rhs) noexcept
			: m_pEmitter(rhs.m_pEmitter)
			, m_eventId(rhs.m_eventId)
			, m_bindingId(rhs.m_bindingId)
		{
		}


		//////////////////////////////////////////////////////////////////////////
		/// Move operator.
		//////////////////////////////////////////////////////////////////////////
		inline HandleBase& HandleBase::operator = (HandleBase&& rhs) noexcept
		{
			m_pEmitter = rhs.m_pEmitter;
			m_eventId = rhs.m_eventId;
			m_bindingId = rhs.m_bindingId;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Comparison operator.
		//////////////////////////////////////////////////////////////////////////
		inline bool HandleBase::operator == (const HandleBase& rhs) const
		{
			return m_pEmitter == rhs.m_pEmitter &&
				m_eventId == rhs.m_eventId &&
				m_bindingId == rhs.m_bindingId;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Get the emitter which the event handler is bound to.
		/// @result pointer to an EventEmitter or null if this is an invalid handle.
		//////////////////////////////////////////////////////////////////////////
		inline EmitterBase* HandleBase::Emitter() const
		{
			return m_pEmitter;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Get the event id of the bound handler.  This id refers to the specific
		/// event and not to the specific instance of a bound handler.
		/// @result the event id which this is bound to.
		//////////////////////////////////////////////////////////////////////////
		inline Id_t HandleBase::EventId() const
		{
			return m_eventId;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Get the unique id of the handler as bound to the event.
		/// @result the id of this specific handler as bound to the specific event.
		//////////////////////////////////////////////////////////////////////////
		inline Id_t HandleBase::BindingId() const
		{
			return m_bindingId;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Invalidate this handle.
		/// When called on a owning handle, this does not remove the event from the
		/// emitter.
		//////////////////////////////////////////////////////////////////////////
		inline void HandleBase::Abandon()
		{
			m_pEmitter = nullptr;
		}



		//////////////////////////////////////////////////////////////////////////
		/// Constructor which takes ownership of a bound handler instance.
		/// @param emitter The emitter which the handler is bound to.
		/// @param the id of the specific event type which the binding refers to.
		/// @param the id of the handler as bound into the event emitter.
		//////////////////////////////////////////////////////////////////////////
		inline Handle::Handle(EmitterBase* emitter, Id_t eventId, Id_t bindingId)
			: HandleBase(emitter, eventId, bindingId)
		{}


		//////////////////////////////////////////////////////////////////////////
		/// Move constructor.  Transfers ownership of the event and invalidates the
		/// old owner handle.
		//////////////////////////////////////////////////////////////////////////
		inline Handle::Handle(Handle&& rhs) noexcept
			: HandleBase(std::move(rhs))
		{
			rhs.m_pEmitter = nullptr;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Move constructor.  Takes ownership of an event from a base non-owning
		/// handle and invalidates the old handle.
		//////////////////////////////////////////////////////////////////////////
		inline Handle::Handle(HandleBase&& rhs) noexcept
			: HandleBase(std::move(rhs))
		{
			rhs.Abandon();
		}


		//////////////////////////////////////////////////////////////////////////
		/// Destructor which removes the event from the emitter.
		//////////////////////////////////////////////////////////////////////////
		inline Handle::~Handle()
		{
			if (Emitter())
			{
				Emitter()->Remove(*this);
			}
		}


		//////////////////////////////////////////////////////////////////////////
		/// Move operator.  Invalidates source handle.
		//////////////////////////////////////////////////////////////////////////
		inline Handle& Handle::operator = (Handle&& rhs) noexcept
		{
			m_pEmitter = rhs.m_pEmitter;
			m_eventId = rhs.m_eventId;
			m_bindingId = rhs.m_bindingId;
			rhs.m_pEmitter = nullptr;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////
		/// Comparison operator.  NOTE: two EventHandles which are equivalent is
		/// illegal unless one is to be abandoned.
		//////////////////////////////////////////////////////////////////////////
		inline bool Handle::operator ==(const Handle& rhs) const
		{
			return m_pEmitter == rhs.m_pEmitter &&
				m_eventId == rhs.m_eventId &&
				m_bindingId == rhs.m_bindingId;
		}
	}
}

/// @cond DETAILS
// Stl integration.
namespace std
{
	template<>
	struct hash < CPF::Events::HandleBase >
	{
		size_t operator ()(const CPF::Events::HandleBase& eh) const
		{
			hash<void*> ptrHash;
			hash<int64_t> intHash;

			size_t emitterHash = ptrHash(eh.Emitter());
			size_t bindingHash = intHash(eh.BindingId());
			size_t eventHash = intHash(eh.EventId());

			size_t combine1 = bindingHash + 0x9e3779b9 + (emitterHash << 6) + (emitterHash >> 2);
			size_t combine2 = eventHash + 0x9e3779b9 + (combine1 << 6) + (combine1 >> 2);
			return combine2;
		}
	};


	template<>
	struct hash < CPF::Events::Handle >
	{
		size_t operator ()(const CPF::Events::Handle& eh) const
		{
			hash<CPF::Events::HandleBase> baseHasher;
			return baseHasher(eh);
		}
	};
}
/// @endcond
