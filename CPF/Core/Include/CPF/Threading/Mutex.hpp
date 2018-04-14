//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Export.hpp"
#include "CPF/Threading/Types.hpp"

namespace CPF
{
	namespace Threading
	{
		//////////////////////////////////////////////////////////////////////////
		/// @brief Basic mutex wrapper.
		//////////////////////////////////////////////////////////////////////////
		class Mutex
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			Mutex(bool initial = false);
			~Mutex();

			//////////////////////////////////////////////////////////////////////////
			void Acquire();
			bool TryAcquire();
			void Release();

			//////////////////////////////////////////////////////////////////////////
			Mutex_t& NativeHandle();

		private:
			//////////////////////////////////////////////////////////////////////////
			Mutex(Mutex&&) = delete;
			Mutex& operator =(Mutex&&) = delete;
			Mutex(const Mutex&) = delete;
			Mutex& operator =(const Mutex&) = delete;

			//////////////////////////////////////////////////////////////////////////
			Mutex_t m_Handle;
		};

		/**
		@brief Constructor.
		@param initial The caller can decide to lock the mutex initially if desired.
		*/
		inline Mutex::Mutex(bool initial)
		{
			::InitializeCriticalSection(&m_Handle);
			if (initial)
				::EnterCriticalSection(&m_Handle);
		}


		inline Mutex::~Mutex()
		{
			::DeleteCriticalSection(&m_Handle);
		}


		/**
		@brief Acquire the mutex.
		*/
		void inline Mutex::Acquire()
		{
			::EnterCriticalSection(&m_Handle);
		}


		/**
		@brief Try to acquire the mutex, returns instantly if unavailable.
		*/
		bool inline Mutex::TryAcquire()
		{
			return ::TryEnterCriticalSection(&m_Handle) == TRUE;
		}


		/**
		@brief Release the mutex.
		*/
		void inline Mutex::Release()
		{
			LeaveCriticalSection(&m_Handle);
		}


		Mutex_t inline &Mutex::NativeHandle()
		{
			return m_Handle;
		}
	}
}
