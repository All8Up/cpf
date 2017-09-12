//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Concurrency.hpp"
#include "Atomic/Atomic.hpp"
#include "Vector.hpp"
#include "Move.hpp"
#include <algorithm>


namespace CPF
{
	namespace Concurrency
	{
		namespace Collections
		{
			/**
			* @brief Implements a multicore ring buffer which performs lazy head adjustments.
			* @tparam TYPE Type of data stored in the ring buffer.
			*/
			template <typename TYPE>
			class RingBuffer
			{
			public:
				static const int64_t InvalidIndex = int64_t(-1);

				RingBuffer(size_t size=4096);
				~RingBuffer();

				bool Initialize(size_t threadCount);

				TYPE& operator [](size_t idx);
				const TYPE& operator [](size_t idx) const;

				int64_t Head() const;
				void Head(int64_t);
				int64_t Tail() const;
				void Tail(int64_t);

				int64_t ThreadHead(int64_t) const;
				void ThreadHead(int64_t, int64_t);

				int64_t Fetch(int64_t, TYPE&);
				void Consume(int tid, int64_t index);

				void Minimize();
				size_t Reclaim(int threadCount);
				size_t Reserve(int threadCount, size_t requested);

				bool PushBack(int threadCount, TYPE&& data);
				void Commit(size_t count);

			private:
				// Internal indexing for each thread.  Should be aligned to cache
				// lines to prevent false sharing.
				struct HeadIndex
				{
					int64_t mHead;
					int8_t pad0[64 - sizeof(int64_t)];
				};

				// Need these to be in individual cache lines to prevent false sharing.
				int64_t mHead;
				int8_t pad0[64 - sizeof(int64_t)];
				int64_t mTail;

				// The rest is all constant after initialization, at least the pointers are.
				// But we pad it out to avoid false sharing with the mTail above.
				int8_t pad1[64 - sizeof(int64_t)];
				int mThreadCount;
				const size_t mSize;
				const size_t mSizeMask;
				HeadIndex* mpThreadHead;
				Vector<TYPE> mBuffer;
			};




			//////////////////////////////////////////////////////////////////////////
			template<typename VALUE_TYPE>
			inline RingBuffer<VALUE_TYPE>::RingBuffer(size_t size)
				: mHead(0)
				, mTail(0)
				, mThreadCount(0)
				, mSize(size)
				, mSizeMask(size - 1)
				, mpThreadHead(nullptr)
			{
				CPF_ASSERT((mSize&(mSize - 1)) == 0);
				mBuffer.resize(size);
			}


			template<typename VALUE_TYPE>
			inline RingBuffer<VALUE_TYPE>::~RingBuffer()
			{
			}

			/**
			* @brief Initializes this object with the expected max number of threads which will call into this.
			* @tparam VALUE_TYPE Type of stored data.
			* @tparam SIZE		  Size of the ring buffer.
			* @param threadCount Number of threads.
			* @return true if it succeeds, false if it fails.
			*/
			template<typename VALUE_TYPE>
			inline bool RingBuffer<VALUE_TYPE>::Initialize(size_t threadCount)
			{
				if (mThreadCount != 0 || mpThreadHead != nullptr)
					return false;
				mpThreadHead = new HeadIndex[threadCount];
				if (mpThreadHead == nullptr)
					return false;
				mThreadCount = int(threadCount);
				for (auto i = 0; i < mThreadCount; ++i)
					mpThreadHead[i].mHead = mHead;
				return true;
			}


			template<typename VALUE_TYPE>
			inline VALUE_TYPE& RingBuffer<VALUE_TYPE>::operator [](size_t idx)
			{
				return mBuffer[idx & mSizeMask];
			}


			template<typename VALUE_TYPE>
			inline const VALUE_TYPE& RingBuffer<VALUE_TYPE>::operator [](size_t idx) const
			{
				return mBuffer[idx & mSizeMask];
			}


			template<typename VALUE_TYPE>
			inline int64_t RingBuffer<VALUE_TYPE>::Head() const
			{
				return Atomic::Load(mHead);
			}


			template<typename VALUE_TYPE>
			inline void RingBuffer<VALUE_TYPE>::Head(int64_t v)
			{
				Atomic::Store(mHead, v);
			}


			template<typename VALUE_TYPE>
			inline int64_t RingBuffer<VALUE_TYPE>::Tail() const
			{
				return Atomic::Load(mTail);
			}


			template<typename VALUE_TYPE>
			inline void RingBuffer<VALUE_TYPE>::Tail(int64_t v)
			{
				return Atomic::Store(mTail, v);
			}


			template<typename VALUE_TYPE>
			inline int64_t RingBuffer<VALUE_TYPE>::ThreadHead(int64_t tid) const
			{
				CPF_ASSERT(tid < mThreadCount);
				return Atomic::Load(mpThreadHead[tid].mHead);
			}


			template<typename VALUE_TYPE>
			inline void RingBuffer<VALUE_TYPE>::ThreadHead(int64_t tid, int64_t v)
			{
				CPF_ASSERT(tid < mThreadCount);
				Atomic::Store(mpThreadHead[tid].mHead, v);
			}


			template<typename VALUE_TYPE>
			inline int64_t RingBuffer<VALUE_TYPE>::Fetch(int64_t tid, VALUE_TYPE& outBuffer)
			{
				CPF_ASSERT(tid < mThreadCount);
				auto tail = Tail();
				auto head = ThreadHead(tid);
				if (head < tail)
				{
					// There is some work to fetch.
					auto ringIndex = head & mSizeMask;
					outBuffer = (*this)[ringIndex];
					CPF_ASSERT(head != InvalidIndex);
					return head;
				}
				return InvalidIndex;
			}


			template<typename TYPE>
			inline void RingBuffer<TYPE>::Consume(int tid, int64_t index)
			{
				CPF_ASSERT(ThreadHead(tid) == index);
				ThreadHead(tid, index+1);
			}



			/**
			* @brief Set all the head indices to a minimal value and update tail.
			* @tparam VALUE_TYPE Type of the value stored in the ring buffer.
			* @tparam SIZE		  Maximum number of items stored, minus one for the sentinel.
			*/
			template<typename VALUE_TYPE>
			inline void RingBuffer<VALUE_TYPE>::Minimize()
			{
				/*
				auto head = Head() % SIZE;
				auto delta = Tail() - Head();
				Head(head);
				Tail(head + delta);
				for (auto i = 0; i < mThreadCount; ++i)
				mpThreadHead[i].mHead = head;
				*/
			}


			/**
			* @brief Reclaims free space in the ring buffer.
			* @tparam VALUE_TYPE Type of the value stored in the ring buffer.
			* @tparam SIZE		  Maximum number of items stored, minus one for the sentinel.
			* @param threadCount Number of threads to test inclusive.
			* @return The number of free slots in the ring buffer.
			*/
			template<typename VALUE_TYPE>
			inline size_t RingBuffer<VALUE_TYPE>::Reclaim(int threadCount)
			{
				CPF_ASSERT(threadCount > 0);
				CPF_ASSERT(threadCount <= mThreadCount);

				// We need to look for the minimal head index in all threads.
				// The minimal location is as far as we can advance the head index.
				auto head = Atomic::Load(mpThreadHead[0].mHead);
				for (auto i = 1; i < threadCount; ++i)
				{
					auto threadIndex = Atomic::Load(mpThreadHead[i].mHead);
					head = (threadIndex < head) ? threadIndex : head;
				}

				Head(head);
				size_t result = (mSize)-(Tail() - head);
				CPF_ASSERT(result <= mSize);
				return result;
			}


			/**
			* @brief Attempts to reserve a number of entries or make them available.
			* @tparam VALUE_TYPE Type of the value stored in the ring buffer.
			* @tparam SIZE		  Maximum number of items stored, minus one for the sentinal.
			* @param requested The number of entries desired.
			* @return The number of entries available.
			*/
			template<typename VALUE_TYPE>
			inline size_t RingBuffer<VALUE_TYPE>::Reserve(int threadCount, size_t requested)
			{
				CPF_ASSERT(threadCount <= mThreadCount);
				if ((Tail() + requested) - Head() >= mSize)
				{
					// Need to reclaim space.
					return std::min(Reclaim(threadCount), requested);
				}

				return requested;
			}


			template<typename TYPE>
			bool RingBuffer<TYPE>::PushBack(int threadCount, TYPE&& data)
			{
				if (Reserve(threadCount, 1))
				{
					mBuffer[(Tail()) & mSizeMask] = CPF::Move(data);
					Commit(1);
					return true;
				}
				return false;
			}


			template<typename TYPE>
			void RingBuffer<TYPE>::Commit(size_t count)
			{
				Atomic::Add(mTail, count);
			}
		}
	}
}
