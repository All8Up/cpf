//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Platform/Threading/Types.hpp"


namespace CPF
{
	namespace Threading
	{
		//////////////////////////////////////////////////////////////////////////
		/// Threading synchronization semaphore.
		//////////////////////////////////////////////////////////////////////////
		class Semaphore
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			Semaphore(int initCount = 0);
			~Semaphore();

			//////////////////////////////////////////////////////////////////////////
			void Acquire();
			void Release(int count = 1);

		private:
			//////////////////////////////////////////////////////////////////////////
			Semaphore(const Semaphore&) = delete;
			Semaphore& operator =(const Semaphore&) = delete;
			Semaphore(Semaphore&&) = delete;
			Semaphore& operator =(Semaphore&&) = delete;

			//////////////////////////////////////////////////////////////////////////
			Semaphore_t m_Handle;
		};

		/**
		* Construct a semaphore.
		* @param initCount The initial count the semaphore starts with.
		*/
		inline Semaphore::Semaphore(int initCount)
			: m_Handle(::CreateSemaphore(nullptr, initCount, 0xFFFF, nullptr))
		{
		}


		inline Semaphore::~Semaphore()
		{
			if (m_Handle != InvalidSemaphore)
				::CloseHandle(m_Handle);
		}


		/**
		* @brief Acquire the semaphore.
		*/
		inline void Semaphore::Acquire()
		{
			::WaitForSingleObject(m_Handle, INFINITE);
		}


		/**
		* @brief Release the semaphore.
		* @param count How many times to release the semaphore.
		*/
		inline void Semaphore::Release(int count)
		{
			::ReleaseSemaphore(m_Handle, count, nullptr);
		}
	}
}
