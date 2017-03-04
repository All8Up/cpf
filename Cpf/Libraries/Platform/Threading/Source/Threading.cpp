//////////////////////////////////////////////////////////////////////////
#include "Threading.hpp"
#include "Threading/Thread.hpp"
#include "Logging/Logging.hpp"
#include "Functional.hpp"
#include "Move.hpp"
#include <thread>


using namespace Cpf;
using namespace Threading;

namespace
{
	int s_RefCount = 0;
}



CPF_EXPORT_THREADING int ThreadingInitializer::Install()
{
	if (s_RefCount++ == 0)
	{
		CPF_INIT_LOG(Concurrency);
		Platform::TimeInitializer::Install();
	}
	return s_RefCount;
}


CPF_EXPORT_THREADING int ThreadingInitializer::Remove()
{
	if (--s_RefCount == 0)
	{
		CPF_DROP_LOG(Concurrency);
		Platform::TimeInitializer::Remove();
	}
	return s_RefCount;
}


//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_THREADING int Threading::GetHardwareConcurrency()
{
	return std::thread::hardware_concurrency();
}


//////////////////////////////////////////////////////////////////////////
Thread::Group::Group()
	: mCount(0)
	, mpThreads(nullptr)
{}


Thread::Group::Group(size_t count)
	: mCount(count)
	, mpThreads(nullptr)
{
	mpThreads = new Thread[count];
}


Thread::Group::Group(Group&& rhs)
	: mCount(rhs.mCount)
	, mpThreads(rhs.mpThreads)
{
	rhs.mCount = 0;
	rhs.mpThreads = nullptr;
}


Thread::Group::~Group()
{
	if (mpThreads)
		Join();
}


Thread::Group& Thread::Group::operator =(Group&& rhs)
{
	CPF_ASSERT(mCount == 0 && mpThreads == nullptr);
	mCount = rhs.mCount;
	mpThreads = rhs.mpThreads;
	rhs.mCount = 0;
	rhs.mpThreads = nullptr;

	return *this;
}


bool Thread::Group::Initialize(size_t count)
{
	CPF_ASSERT(mpThreads == nullptr && mCount == 0);
	mpThreads = new Thread[count];
	if (mpThreads)
	{
		mCount = count;
		return true;
	}
	return false;
}


void Thread::Group::Join()
{
	if (mpThreads)
	{
		for (auto i = 0; i < mCount; ++i)
			mpThreads[i].Join();
		delete[] mpThreads;
		mCount = 0;
		mpThreads = nullptr;
	}
}


Thread::Group::operator bool() const
{
	return mCount != 0;
}


size_t Thread::Group::Size() const
{
	return mCount;
}


void Thread::Group::_Start(size_t index, Function<void(void)> func)
{
	CPF_ASSERT(mpThreads != nullptr && mCount > index);
	mpThreads[index](Cpf::Move(func));
}


void Thread::Group::_Start(Function<void(void)> start)
{
	for (auto i = 0; i < mCount; ++i)
	{
		Function<void(void)>  startCopy = start;
		mpThreads[i](Cpf::Move(startCopy));
	}
}
