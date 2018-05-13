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
			Reactor(Reactor&&) = delete;
			Reactor(const Reactor&) = delete;
			~Reactor() = default;

			Reactor& operator =(Reactor&&) = delete;
			Reactor& operator =(const Reactor&) = delete;

			bool Run();
			bool RunOne();
			void Quit();

			class Queue;
			Queue GetQueue();

		private:
			bool mExit;
			Mutex mLock;
			ConditionVariable mCondition;
			CPF_DLL_SAFE_BEGIN;
			STD::Queue<WorkFunction> mQueue;
			CPF_DLL_SAFE_END;
		};


		/** @brief The queue feeder.  Push work in here, it comes out in the reactor. */
		class Reactor::Queue
		{
		public:			
			using WorkFunction = WorkFunction;

			Queue() = default;
			Queue(const Queue&) = delete;
			Queue(Queue&&) = default;
			~Queue() = default;

			Queue& operator = (const Queue&) = delete;
			Queue& operator = (Queue&&) = default;

			void operator ()(WorkFunction&) const;
			void operator ()(WorkFunction&&) const;

		private:
			friend class Reactor;

			explicit Queue(Reactor*);

			Reactor* mpReactor;
		};


		/** @brief Default constructor. */
		inline Reactor::Reactor()
			: mExit(false)
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
					const auto func = STD::Move(mQueue.front());
					mQueue.pop();

					// Execute the work.  Unlock while working so as not to deadlock.
					mLock.Release();
					func();
					mLock.Acquire();
				}

				// Check for exit.
				if (mExit)
				{
					const auto result = mQueue.empty();
					mLock.Release();
					return result;
				}

				// Wait for some work or the exit signal.
				mCondition.Acquire(mLock);
			}
		}


		/**
		* @brief Runs one item in the work queue.
		* @return true if it succeeds in running work, false if there is nothing to do.
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
			const auto func = STD::Move(mQueue.front());
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

		inline Reactor::Queue Reactor::GetQueue()
		{
			return Queue(this);
		}

		//////////////////////////////////////////////////////////////////////////
		/**
		* @brief Constructor.
		* @param [in,out] reactor If non-null, the reactor.
		*/
		inline Reactor::Queue::Queue(Reactor* reactor)
			: mpReactor(reactor)
		{}

		/**
		* @brief Push a work function onto the work queue.
		* @param [in,out] func The function.
		*/
		inline void Reactor::Queue::operator ()(WorkFunction& func) const
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
		inline void Reactor::Queue::operator ()(WorkFunction&& func) const
		{
			mpReactor->mLock.Acquire();
			mpReactor->mQueue.push(func);
			mpReactor->mLock.Release();
			mpReactor->mCondition.ReleaseAll();
		}
	}
}
