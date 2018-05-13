//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Export.hpp"
#include "CPF/Time.hpp"
#include "CPF/STD/Functional.hpp"
#include <thread>

namespace CPF
{
	namespace Threading
	{
		class Thread : std::thread
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			class Group;

			//////////////////////////////////////////////////////////////////////////
			Thread() {}
			Thread(Thread&& rhs) noexcept { swap(rhs); }
			~Thread() {}

			//////////////////////////////////////////////////////////////////////////
			template<typename FUNCTION, typename... ARGS>
			explicit Thread(FUNCTION&& func, ARGS&&... args);

			Thread& operator = (Thread&& rhs) noexcept { swap(rhs); return *this; }

			//////////////////////////////////////////////////////////////////////////
			void Join()
			{
				join();
			}

			//////////////////////////////////////////////////////////////////////////
			static void Sleep(const Time::Value& tp)
			{
				const auto ms = int64_t(Time::Ms(tp));
				std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			}
			static void Pause()
			{
				_mm_pause();
			}
			static void GetThreadTimes(Time::Value& userTime, Time::Value& kernelTime)
			{
				FILETIME unused;
				FILETIME kernel, user;
				const HANDLE handle = ::GetCurrentThread();
				::GetThreadTimes(handle, &unused, &unused, &kernel, &user);

				const uint64_t kernel64 = (uint64_t(kernel.dwHighDateTime) << 32) + kernel.dwLowDateTime;
				const uint64_t user64 = (uint64_t(user.dwHighDateTime) << 32) + user.dwLowDateTime;

				// Convert the time from FILETIME 100ns multiples to time value.
				using oneHundredNs = Time::UnitBase<int64_t, 1, 10000000>;
				kernelTime = oneHundredNs(kernel64);
				userTime = oneHundredNs(user64);
			}
			static void SetName(const char* name)
			{
#pragma pack(push,8)
				typedef struct tagTHREADNAME_INFO
				{
					DWORD dwType; // Must be 0x1000.
					LPCSTR szName; // Pointer to name (in user addr space).
					DWORD dwThreadID; // Thread ID (-1=caller thread).
					DWORD dwFlags; // Reserved for future use, must be zero.
				} THREADNAME_INFO;
#pragma pack(pop)

				const DWORD MS_VC_EXCEPTION = 0x406D1388;
				THREADNAME_INFO info;
				info.dwType = 0x1000;
				info.szName = name;
				info.dwThreadID = ::GetThreadId(::GetCurrentThread());
				info.dwFlags = 0;

				__try
				{
					RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), reinterpret_cast<ULONG_PTR*>(&info));
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
				}
			}
			static int GetHardwareThreadCount() { return hardware_concurrency(); }

		private:
			//////////////////////////////////////////////////////////////////////////
			Thread(const Thread&) = delete;
			const Thread& operator =(const Thread&) = delete;
		};

		/**
		* @brief Thread constructor which takes the function and arguments to call.
		* @param func The thread function to run.
		* @param args The arguments sent to the thread function.
		*/
		template<typename FUNCTION, typename... ARGS>
		Thread::Thread(FUNCTION&& func, ARGS&&... args)
			: std::thread(std::forward<FUNCTION>(func), std::forward<ARGS>(args)...)
		{
		}
	}
}

#include "CPF/Threading/ThreadGroup.hpp"
