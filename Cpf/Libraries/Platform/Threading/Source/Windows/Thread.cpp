//////////////////////////////////////////////////////////////////////////
#include "Threading/Thread.hpp"
#include "Time/Unit.hpp"
#include "Time/Value.hpp"
#include <thread>

using namespace Cpf;
using namespace Threading;

namespace
{
	DWORD WINAPI OsThreadRunner(LPVOID startData)
	{
		std::function<void(void)>* tramp = reinterpret_cast<Function<void(void)>*>(startData);
		(*tramp)();
		delete tramp;
		return 0;
	}
}


void CPF_EXPORT_THREADING Thread::_Start(Function<void(void)>&& func)
{
	std::function<void(void)>* funcData = new Function< void(void) > ;
	*funcData = Move(func);

	NativeHandle() = CreateThread(
		nullptr,
		0,
		&OsThreadRunner,
		funcData,
		0,
		nullptr
		);
}


/**
@brief Default constructor.  Creates a thread object in an invalid state.
*/
Thread::Thread()
	: m_Handle(InvalidThread)
{
}


/**
@brief Destructor.  Does not attempt to validate shutdown of the thread or force it to shutdown.
*/
Thread::~Thread()
{
	::CloseHandle(m_Handle);
}


/**
@brief Blocks until the thread exits.
*/
void Thread::Join()
{
	::WaitForSingleObject(m_Handle, INFINITE);
}


/**
@brief Put the thread to sleep for the given time value.
@param tp The amount of time to put the thread to sleep.
*/
void Thread::Sleep(const Platform::Time::Value& tp)
{
	auto ms = int64_t(Platform::Time::Ms(tp));
	::SleepEx(DWORD(ms), TRUE);
}


/**
@brief Put the thread into a pause state momentarily.  Used in spin locks for exponential back off.
*/
void Thread::Pause()
{
	_mm_pause();
}


/**
@brief Get time information about this thread.
@param userTime Time spent in user code.
@param kernelTime Time spent in kernel code.
*/
void Thread::GetThreadTimes(Platform::Time::Value& userTime, Platform::Time::Value& kernelTime)
{
	FILETIME unused;
	FILETIME kernel, user;
	HANDLE handle = ::GetCurrentThread();
	::GetThreadTimes(handle, &unused, &unused, &kernel, &user);

	uint64_t kernel64 = (((uint64_t)kernel.dwHighDateTime) << 32) + kernel.dwLowDateTime;
	uint64_t user64 = (((uint64_t)user.dwHighDateTime) << 32) + user.dwLowDateTime;

	// Convert the time from FILETIME 100ns multiples to time value.
	using oneHundredNs = Platform::Time::UnitBase < int64_t, 1, 10000000 >;
	kernelTime = oneHundredNs(kernel64);
	userTime = oneHundredNs(user64);
}


/**
@brief Set the name of the thread for debugging and profiling systems.
@param name Set the name of the thread for debuggers.
*/
void Thread::SetName(const char* name)
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
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}


/**
	* @brief Get the number of available hardware threads.
	*/
int Thread::GetHardwareThreadCount()
{
	return std::thread::hardware_concurrency();
}


Thread_t& Thread::NativeHandle()
{
	return m_Handle;
}
