//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Threading/Thread.hpp"

namespace CPF
{
	namespace Threading
	{
		//////////////////////////////////////////////////////////////////////////
		/**
		* @brief A container for a group of threads.
		*/
		class Thread::Group
		{
		public:
			Group();
			Group(size_t count);
			explicit Group(Group&&);
			~Group();

			Group& operator =(Group&&);

			bool Initialize(size_t count);

			template<typename tFunction>
			void operator ()(tFunction&& func);

			template<typename tFunction>
			void operator ()(size_t index, tFunction&& func);

			void Join();

			explicit operator bool() const;

			size_t Size() const;

		private:
			Group(const Group&) = delete;
			const Group& operator =(const Group&) = delete;

			void _Start(size_t index, Function<void()>);
			void _Start(Function<void()>);

			size_t mCount;
			Thread* mpThreads;
		};


		template<typename tFunction>
		void Thread::Group::operator ()(tFunction&& func)
		{
			_Start(Move(func));
		};


		template<typename tFunction>
		void Thread::Group::operator ()(size_t index, tFunction&& func)
		{
			_Start(index, Move(func));
		};

		inline Thread::Group::Group()
			: mCount(0)
			, mpThreads(nullptr)
		{}


		inline Thread::Group::Group(size_t count)
			: mCount(count)
			, mpThreads(nullptr)
		{
			mpThreads = new Thread[count];
		}


		inline Thread::Group::Group(Group&& rhs)
			: mCount(rhs.mCount)
			, mpThreads(rhs.mpThreads)
		{
			rhs.mCount = 0;
			rhs.mpThreads = nullptr;
		}


		inline Thread::Group::~Group()
		{
			if (mpThreads)
				Join();
		}


		inline Thread::Group& Thread::Group::operator =(Group&& rhs)
		{
			CPF_ASSERT(mCount == 0 && mpThreads == nullptr);
			mCount = rhs.mCount;
			mpThreads = rhs.mpThreads;
			rhs.mCount = 0;
			rhs.mpThreads = nullptr;

			return *this;
		}


		inline bool Thread::Group::Initialize(size_t count)
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


		inline void Thread::Group::Join()
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


		inline Thread::Group::operator bool() const
		{
			return mCount != 0;
		}


		inline size_t Thread::Group::Size() const
		{
			return mCount;
		}


		inline void Thread::Group::_Start(size_t index, Function<void(void)> func)
		{
			CPF_ASSERT(mpThreads != nullptr && mCount > index);
			mpThreads[index](Move(func));
		}


		inline void Thread::Group::_Start(Function<void()> start)
		{
			for (auto i = 0; i < mCount; ++i)
			{
				Function<void()>  startCopy = start;
				mpThreads[i](Move(startCopy));
			}
		}
	}
}
