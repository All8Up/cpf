//////////////////////////////////////////////////////////////////////////
#include "Threading/Reactor.hpp"
#include "Move.hpp"
#include "Threading/ScopedLock.hpp"

using namespace Cpf;
using namespace Threading;


/** @brief Default constructor. */
Reactor::Reactor()
	: mExit(false)
{}


/** @brief Destructor. */
Reactor::~Reactor()
{}


/**
 * @brief Runs the work queue until told to exit.
 * @return true if it succeeds, false if it fails.
 */
bool Reactor::Run()
{
	WorkFunction func;
	for (;;)
	{
		// Check for work.
		mLock.Acquire();

		// Do as much work as possible.
		while (!mQueue.empty())
		{
			// Get something off the queue.
			func = Move(mQueue.front());
			mQueue.pop();

			// Execute the work.  Unlock while working so as not to deadlock.
			mLock.Release();
			func();
			mLock.Acquire();
		}

		// Check for exit.
		if (mExit)
		{
			bool result = mQueue.empty();
			mLock.Release();
			return result;
		}

		// Wait for some work or the exit signal.
		mCondition.Acquire(mLock);
	}
}


/**
 * @brief Runs one item in the work queue.
 * @return true if it succeeds, false if it fails.
 */
bool Reactor::RunOne()
{
	// Check for work.
	mLock.Acquire();
	if (mQueue.empty())
	{
		mLock.Release();
		return false;
	}

	// Get the work.
	WorkFunction func = Move(mQueue.front());
	mQueue.pop();
	mLock.Release();

	// Execute the work.
	func();
	return true;
}


/** @brief Stops execution of the work queue. */
void Reactor::Quit()
{
	mLock.Acquire();
	mExit = true;
	mLock.Release();
	mCondition.ReleaseAll();
}


//////////////////////////////////////////////////////////////////////////
/** @brief Default constructor. */
Reactor::WorkQueue::WorkQueue()
: mpReactor(nullptr)
{}


/**
 * @brief Constructor.
 * @param [in,out] reactor If non-null, the reactor.
 */
Reactor::WorkQueue::WorkQueue(Reactor* reactor)
: mpReactor(reactor)
{}


/**
 * @brief Initializes this object.
 * @param [in,out] reactor If non-null, the reactor.
 */
void Reactor::WorkQueue::Initialize(Reactor* reactor)
{
	mpReactor = reactor;
}


/**
 * @brief Push a work function onto the work queue.
 * @param [in,out] func The function.
 */
void Reactor::WorkQueue::operator ()(WorkFunction& func) const
{
	mpReactor->mLock.Acquire();
	mpReactor->mQueue.push(Move(func));
	mpReactor->mLock.Release();
	mpReactor->mCondition.ReleaseAll();
}


/**
 * @brief Push a work function onto the work queue.
 * @param [in,out] func The function.
 */
void Reactor::WorkQueue::operator ()(WorkFunction&& func) const
{
	mpReactor->mLock.Acquire();
	mpReactor->mQueue.push(func);
	mpReactor->mLock.Release();
	mpReactor->mCondition.ReleaseAll();
}
