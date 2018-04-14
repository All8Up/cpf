//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/CSTD/Memory.hpp"
#include "CPF/Threading/ThreadLocal.hpp"
#include <atomic>

namespace CPF
{
	namespace Memory
	{
		/**
		 * A simple handle based scratch allocation system.
		 */
		template <int ALIGNMENT = 16, size_t INITSIZE=256>
		class ScratchAllocator
		{
		public:
			static constexpr int kAlignment = ALIGNMENT;
			static constexpr int kInitSize = INITSIZE;

			enum Handle : intptr_t { eInvalid = intptr_t(-1) };

			ScratchAllocator();
			ScratchAllocator(const ScratchAllocator&) = delete;
			ScratchAllocator(ScratchAllocator&&) = delete;
			~ScratchAllocator();

			ScratchAllocator& operator = (const ScratchAllocator&) = delete;
			ScratchAllocator& operator = (ScratchAllocator&&) = delete;

			Handle Alloc(size_t size);
			void* Get(Handle handle) const;
			void Reset();

			size_t Size() const;
			size_t Capacity() const;

			bool Reserve(size_t capacity);
			void* Data() const;

		private:
			uint8_t* mpBegin;
			uint8_t* mpEnd;
			size_t mCapacity;
		};

		template <int ALIGNMENT, size_t INITSIZE>
		ScratchAllocator<ALIGNMENT, INITSIZE>::ScratchAllocator()
			: mpBegin(nullptr)
			, mpEnd(nullptr)
			, mCapacity(0)
		{
			Reserve(INITSIZE);
		}

		template <int ALIGNMENT, size_t INITSIZE>
		ScratchAllocator<ALIGNMENT, INITSIZE>::~ScratchAllocator()
		{
			if (mpBegin)
				_aligned_free(mpBegin);
		}

		template <int ALIGNMENT, size_t INITSIZE>
		typename ScratchAllocator<ALIGNMENT, INITSIZE>::Handle ScratchAllocator<ALIGNMENT, INITSIZE>::Alloc(size_t size)
		{
			const auto targetSize = ((size + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;
			if (Capacity() - Size() < targetSize)
				if (!Reserve(mCapacity * 2))
					return eInvalid;

			const auto result = mpEnd - mpBegin;
			mpEnd += targetSize;

			return Handle(result);
		}

		template <int ALIGNMENT, size_t INITSIZE>
		void* ScratchAllocator<ALIGNMENT, INITSIZE>::Get(Handle handle) const
		{
			return mpBegin + intptr_t(handle);
		}

		template <int ALIGNMENT, size_t INITSIZE>
		void ScratchAllocator<ALIGNMENT, INITSIZE>::Reset()
		{
			mpEnd = mpBegin;
		}

		template <int ALIGNMENT, size_t INITSIZE>
		size_t ScratchAllocator<ALIGNMENT, INITSIZE>::Size() const
		{
			return mpEnd - mpBegin;
		}

		template <int ALIGNMENT, size_t INITSIZE>
		size_t ScratchAllocator<ALIGNMENT, INITSIZE>::Capacity() const
		{
			return mCapacity;
		}

		template <int ALIGNMENT, size_t INITSIZE>
		bool ScratchAllocator<ALIGNMENT, INITSIZE>::Reserve(size_t capacity)
		{
			if (capacity <= Size())
				return true;

			const size_t target = ((capacity + (ALIGNMENT - 1)) / ALIGNMENT) * ALIGNMENT;
			uint8_t* newBuffer = reinterpret_cast<uint8_t*>(_aligned_malloc(target, ALIGNMENT));
			if (newBuffer)
			{
				if (mpBegin)
				{
					CSTD::MemCpy(newBuffer, mpBegin, Size());
					_aligned_free(mpBegin);
				}
				mpEnd = newBuffer + Size();
				mpBegin = newBuffer;
				mCapacity = target;

				return true;
			}
			return false;
		}

		template <int ALIGNMENT, size_t INITSIZE>
		void* ScratchAllocator<ALIGNMENT, INITSIZE>::Data() const
		{
			return mpBegin;
		}
	}
}
