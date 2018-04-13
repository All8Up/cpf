//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Export.hpp"
#include "CPF/Threading/Mutex.hpp"
#include "CPF/Threading/ConditionVariable.hpp"
#include "CPF/Std/Queue.hpp"
#include "CPF/Std/Functional.hpp"
#include "CPF/Std/Move.hpp"


namespace CPF
{
	namespace Threading
	{
		/** @brief A reactor can be owned by a worker thread, other threads
		 *	can post work to a WorkQueue for the owner to execute.
		 */
		class Reactor
		{
		public:
			using WorkFunction = STD::Function<void()>;

			Reactor();
			~Reactor();

			bool Run();
			bool RunOne();
			void Quit();

		private:
			friend class ReactorQueue;
			
			Reactor(Reactor&&) = delete;
			Reactor(const Reactor&) = delete;
			Reactor& operator =(Reactor&&) = delete;
			Reactor& operator =(const Reactor&) = delete;

			bool mExit;
			Mutex mLock;
			ConditionVariable mCondition;
			CPF_DLL_SAFE_BEGIN;
			STD::Queue<WorkFunction> mQueue;
			CPF_DLL_SAFE_END;
		};


		/** @brief The queue feeder.  Push work in here, it comes out in the reactor. */
		class ReactorQueue
		{
		public:
			ReactorQueue();
			ReactorQueue(Reactor*);
			
			using WorkFunction = Reactor::WorkFunction;

			void Initialize(Reactor*);

			void operator ()(WorkFunction&) const;
			void operator ()(WorkFunction&&) const;

		private:
			ReactorQueue(const ReactorQueue&) = delete;
			ReactorQueue(ReactorQueue&&) = delete;
			ReactorQueue& operator = (const ReactorQueue&) = delete;
			ReactorQueue& operator = (ReactorQueue&&) = delete;

			Reactor* mpReactor;
		};


		/** @brief Default constructor. */
		inline Reactor::Reactor()
			: mExit(false)
		{}


		/** @brief Destructor. */
		inline Reactor::~Reactor()
		{}


		/**
		* @brief Runs the work queue until told to exit.
		* @return true if it succeeds, false if it fails.
		*/
		inline bool Reactor::Run()
		{
			// Initialize the loop with the lock taken.
			mLock.Acquire();

			for (;;)
			{
				// Do as much work as possible.
				while (!mQueue.empty())
				{
					// Get something off the queue.
					WorkFunction func = STD::Move(mQueue.front());
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
		inline bool Reactor::RunOne()
		{
			// Check for work.
			mLock.Acquire();
			if (mQueue.empty())
			{
				mLock.Release();
				return false;
			}

			// Get the work.
			WorkFunction func = STD::Move(mQueue.front());
			mQueue.pop();
			mLock.Release();

			// Execute the work.
			func();
			return true;
		}


		/** @brief Stops execution of the work queue. */
		inline void Reactor::Quit()
		{
			mLock.Acquire();
			mExit = true;
			mLock.Release();
			mCondition.ReleaseAll();
		}


		//////////////////////////////////////////////////////////////////////////
		/** @brief Default constructor. */
		inline ReactorQueue::ReactorQueue()
			: mpReactor(nullptr)
		{}


		/**
		* @brief Constructor.
		* @param [in,out] reactor If non-null, the reactor.
		*/
		inline ReactorQueue::ReactorQueue(Reactor* reactor)
			: mpReactor(reactor)
		{}


		/**
		* @brief Initializes this object.
		* @param [in,out] reactor If non-null, the reactor.
		*/
		inline void ReactorQueue::Initialize(Reactor* reactor)
		{
			mpReactor = reactor;
		}


		/**
		* @brief Push a work function onto the work queue.
		* @param [in,out] func The function.
		*/
		inline void ReactorQueue::operator ()(WorkFunction& func) const
		{
			mpReactor->mLock.Acquire();
			mpReactor->mQueue.push(STD::Move(func));
			mpReactor->mLock.Release();
			mpReactor->mCondition.ReleaseAll();
		}


		/**
		* @brief Push a work function onto the work queue.
		* @param [in,out] func The function.
		*/
		inline void ReactorQueue::operator ()(WorkFunction&& func) const
		{
			mpReactor->mLock.Acquire();
			mpReactor->mQueue.push(func);
			mpReactor->mLock.Release();
			mpReactor->mCondition.ReleaseAll();
		}
	}
}
