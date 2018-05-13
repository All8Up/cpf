//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Move.hpp"
#include <algorithm>
#include <atomic>

namespace CPF
{
	namespace Platform
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
				static const int64_t kInvalidIndex = int64_t(-1);

				RingBuffer(size_t size=4096);
				~RingBuffer();

				bool Initialize(size_t threadCount);

				TYPE& operator [](size_t idx);
				const TYPE& operator [](size_t idx) const;

				int64_t GetTail() const;
				void SetThreadHead(int64_t, int64_t);

				int64_t Fetch(int64_t, TYPE&);
				void ConsumeThreadHead(int tid);

				size_t Reclaim(int threadCount);
				size_t Reserve(int threadCount, size_t requested);

				bool PushBack(int threadCount, TYPE&& data);

				void Commit(size_t count);

			private:
				// Internal functionality.
				int64_t GetThreadHead(int64_t) const;
				int64_t GetHead() const;
				void SetHead(int64_t);
				void SetTail(int64_t);

				// Internal indexing for each thread.  Should be aligned to cache
				// lines to prevent false sharing.
				struct HeadIndex
				{
					std::atomic<int64_t> mHead;
					int8_t pad0[64 - sizeof(int64_t)];
				};

				// Need these to be in individual cache lines to prevent false sharing.
				std::atomic<int64_t> mHead;
				int8_t pad0[64 - sizeof(int64_t)];
				std::atomic<int64_t> mTail;

				// The rest is all constant after initialization, at least the pointers are.
				// But we pad it out to avoid false sharing with the mTail above.
				int8_t pad1[64 - sizeof(int64_t)];
				int mThreadCount;
				const size_t mSize;
				const size_t mSizeMask;
				HeadIndex* mpThreadHead;
				TYPE* mpBuffer;
			};


			/**
			 @brief Constructor
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param size The sizeof the ring buffer.
			 */
			template<typename VALUE_TYPE>
			RingBuffer<VALUE_TYPE>::RingBuffer(size_t size)
				: mHead(0)
				, mTail(0)
				, mThreadCount(0)
				, mSize(size)
				, mSizeMask(size - 1)
				, mpThreadHead(nullptr)
			{
				CPF_ASSERT((mSize&(mSize - 1)) == 0);
				mpBuffer = new VALUE_TYPE[size];
			}

			/**
			 @brief Destructor
			 @tparam VALUE_TYPE Type of the contained elements.
			 */
			template<typename VALUE_TYPE>
			RingBuffer<VALUE_TYPE>::~RingBuffer()
			{
				delete[] mpBuffer;
			}

			/**
			* @brief Initializes this object with the expected max number of threads which will call into this.
			* @tparam VALUE_TYPE Type of stored data.
			* @param threadCount Number of threads.
			* @return true if it succeeds, false if it fails.
			*/
			template<typename VALUE_TYPE>
			bool RingBuffer<VALUE_TYPE>::Initialize(size_t threadCount)
			{
				if (mThreadCount != 0 || mpThreadHead != nullptr)
					return false;
				mpThreadHead = new HeadIndex[threadCount];
				if (mpThreadHead == nullptr)
					return false;
				mThreadCount = int(threadCount);
				for (auto i = 0; i < mThreadCount; ++i)
					mpThreadHead[i].mHead.store(mHead);
				return true;
			}

			/**
			 @brief Array indexer operator
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param idx Zero-based index of the element.
			 @return The element at the given index.
			 */
			template<typename VALUE_TYPE>
			VALUE_TYPE& RingBuffer<VALUE_TYPE>::operator [](size_t idx)
			{
				return mpBuffer[idx & mSizeMask];
			}

			/**
			 @brief Array indexer operator
			 @tparam VALUE_TYPE Type of the value type.
			 @param idx Zero-based index of the element.
			 @return The element at the given index.
			 */
			template<typename VALUE_TYPE>
			const VALUE_TYPE& RingBuffer<VALUE_TYPE>::operator [](size_t idx) const
			{
				return mpBuffer[idx & mSizeMask];
			}

			/**
			 @brief Get the head index of the ring buffer.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @return The head index.
			 */
			template<typename VALUE_TYPE>
			int64_t RingBuffer<VALUE_TYPE>::GetHead() const
			{
				return mHead.load();
			}

			/**
			 @brief Sets the global head index of the ring buffer.
			 Always <= to the minimum of all thread specific head values.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param v The new head index.
			 */
			template<typename VALUE_TYPE>
			void RingBuffer<VALUE_TYPE>::SetHead(int64_t v)
			{
				mHead.store(v);
			}

			/**
			 @brief Gets the tail of the ring buffer.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @return The tail index.
			 */
			template<typename VALUE_TYPE>
			int64_t RingBuffer<VALUE_TYPE>::GetTail() const
			{
				return mTail.load();
			}

			/**
			 @brief Sets the tail index of the ring buffer.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param v The index of the new last element.
			 */
			template<typename VALUE_TYPE>
			void RingBuffer<VALUE_TYPE>::SetTail(int64_t v)
			{
				return mTail.store(v);
			}

			/**
			 @brief Gets thread specific head index.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param tid The thread id.
			 @return The thread specific index.
			 */
			template<typename VALUE_TYPE>
			int64_t RingBuffer<VALUE_TYPE>::GetThreadHead(int64_t tid) const
			{
				CPF_ASSERT(tid < mThreadCount);
				return mpThreadHead[tid].mHead.load();
			}

			/**
			 @brief Sets a thread specific head index.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param tid The thread id of the thread specific head to change.
			 @param v The value to store in the thread specific head value.
			 */
			template<typename VALUE_TYPE>
			void RingBuffer<VALUE_TYPE>::SetThreadHead(int64_t tid, int64_t v)
			{
				CPF_ASSERT(tid < mThreadCount);
				mpThreadHead[tid].mHead.store(v);
			}

			/**
			 @brief Fetches an element from the ring buffer.
			 @tparam VALUE_TYPE Type of the contained elements.
			 @param tid The thread id which is attempting the fetch.
			 @param [in,out] The resulting value.
			 @return The new head index or invalid index if there is nothing to fetch.
			 */
			template<typename VALUE_TYPE>
			int64_t RingBuffer<VALUE_TYPE>::Fetch(int64_t tid, VALUE_TYPE& outBuffer)
			{
				CPF_ASSERT(tid < mThreadCount);
				auto tail = GetTail();
				auto head = GetThreadHead(tid);
				if (head < tail)
				{
					// There is some work to fetch.
					auto ringIndex = head & mSizeMask;
					outBuffer = (*this)[ringIndex];
					CPF_ASSERT(head != kInvalidIndex);
					return head;
				}
				return kInvalidIndex;
			}

			/**
			 @brief Consume elements in the ring buffer up to the given threads head index.
			 @tparam TYPE Type of the contained elements.
			 @param tid The tid.
			 */
			template<typename TYPE>
			void RingBuffer<TYPE>::ConsumeThreadHead(int tid)
			{
				SetThreadHead(tid, GetThreadHead(tid) + 1);
			}

			/**
			* @brief Reclaims free space in the ring buffer.
			* @tparam VALUE_TYPE Type of the value stored in the ring buffer.
			* @tparam SIZE Maximum number of items stored, minus one for the sentinel.
			* @param threadCount Number of threads to test inclusive.
			* @return The number of free slots in the ring buffer.
			*/
			template<typename VALUE_TYPE>
			size_t RingBuffer<VALUE_TYPE>::Reclaim(int threadCount)
			{
				CPF_ASSERT(threadCount > 0);
				CPF_ASSERT(threadCount <= mThreadCount);

				// We need to look for the minimal head index in all threads.
				// The minimal location is as far as we can advance the head index.
				auto head = mpThreadHead[0].mHead.load();
				for (auto i = 1; i < threadCount; ++i)
				{
					auto threadIndex = mpThreadHead[i].mHead.load();
					head = (threadIndex < head) ? threadIndex : head;
				}

				SetHead(head);
				size_t result = (mSize)-(GetTail() - head);
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
				if ((GetTail() + requested) - GetHead() >= mSize)
				{
					// Need to reclaim space.
					return Reclaim(threadCount) < requested ? Reclaim(threadCount) : requested;
				}

				return requested;
			}

			/**
			 @brief Pushes a new element onto the buffer and commits it if possible.
			 @tparam TYPE Type of the contained elements.
			 @param threadCount Number of threads currently active in the system.
			 @param [in,out] New element to be appended.
			 @return True if it succeeds, false if it fails.
			 */
			template<typename TYPE>
			bool RingBuffer<TYPE>::PushBack(int threadCount, TYPE&& data)
			{
				if (Reserve(threadCount, 1))
				{
					mpBuffer[(GetTail()) & mSizeMask] = STD::Move(data);
					Commit(1);
					return true;
				}
				return false;
			}

			/**
			 @brief Commits a number of elements to be processed.
			 @tparam TYPE Type of the contained elements.
			 @param count Number of elements which will become available.
			 */
			template<typename TYPE>
			void RingBuffer<TYPE>::Commit(size_t count)
			{
				mTail.fetch_add(count);
			}
		}
	}
}
