//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/STD/Vector.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace STD
	{
		/**
		@brief A container of elements with free list packing.
		This does not perform versioning or any other form of validation so
		this is not appropriate to use as a handle pool.  It is targeted
		towards internal structures which validate indexing prior to access.
		@tparam ElementType Type of the index being stored.
		@tparam BlockSize Size of blocks to allocate on expansion.
		*/
		template <typename ElementType, size_t BlockSize = 1024>
		class PoolVector
		{
		public:
			enum class Handle : size_t { eInvalid = size_t(-1) };

			PoolVector();
			~PoolVector();

			Handle Alloc();
			Handle Alloc(const ElementType& initData);
			void Free(Handle);

			const ElementType& operator [](Handle handle) const;
			ElementType& operator [](Handle handle);

		private:
			void Expand(size_t targetSize);
			ElementType& AsElement(size_t index) { return *reinterpret_cast<ElementType*>(mIndices[index].mData); }
			const ElementType& AsElement(size_t index) const { return *reinterpret_cast<const ElementType*>(mIndices[index].mData); }

			using IndexType = uint32_t;
			union Element
			{
				uint8_t alignas(alignof(ElementType)) mData[sizeof(ElementType)];
				IndexType mNextSlot;
			};

			using ElementStorage = Vector<Element>;

			ElementStorage mIndices;
			static constexpr IndexType kInvalidSlot = IndexType(-1);
			IndexType mFirstFree;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename ElementType, size_t BlockSize>
		PoolVector<ElementType, BlockSize>::PoolVector()
			: mFirstFree(IndexType(-1))
		{
			Expand(BlockSize);
		}

		template <typename ElementType, size_t BlockSize>
		PoolVector<ElementType, BlockSize>::~PoolVector()
		{}

		template <typename ElementType, size_t BlockSize>
		typename PoolVector<ElementType, BlockSize>::Handle PoolVector<ElementType, BlockSize>::Alloc()
		{
			if (mFirstFree == kInvalidSlot)
				Expand(mIndices.size() + 1);
			const auto result = Handle(mFirstFree);
			mFirstFree = mIndices[mFirstFree].mNextSlot;
			new (mIndices[size_t(result)].mData) ElementType();
			return result;
		}

		template <typename ElementType, size_t BlockSize>
		typename PoolVector<ElementType, BlockSize>::Handle PoolVector<ElementType, BlockSize>::Alloc(const ElementType& initData)
		{
			if (mFirstFree == kInvalidSlot)
				Expand(mIndices.size() + 1);
			const auto result = Handle(mFirstFree);
			mFirstFree = mIndices[mFirstFree].mNextSlot;
			new (mIndices[size_t(result)].mData) ElementType();
			AsElement(size_t(result)) = initData;
			return result;
		}

		template <typename ElementType, size_t BlockSize>
		void PoolVector<ElementType, BlockSize>::Free(Handle handle)
		{
			// TODO: Make mFirstFree always point to the lowest index.
			CPF_ASSERT(IndexType(handle) >= IndexType(0) && IndexType(handle) < IndexType(mIndices.size()));
			AsElement(size_t(handle)).~ElementType();
			mIndices[size_t(handle)].mNextSlot = mFirstFree;
			mFirstFree = IndexType(handle);
		}

		template <typename ElementType, size_t BlockSize>
		const ElementType& PoolVector<ElementType, BlockSize>::operator [](Handle handle) const
		{
			CPF_ASSERT(IndexType(handle) >= IndexType(0) && IndexType(handle) < IndexType(mIndices.size()));
			return AsElement(size_t(handle));
		}

		template <typename ElementType, size_t BlockSize>
		ElementType& PoolVector<ElementType, BlockSize>::operator [](Handle handle)
		{
			CPF_ASSERT(IndexType(handle) >= IndexType(0) && IndexType(handle) < IndexType(mIndices.size()));
			return AsElement(size_t(handle));
		}

		template <typename ElementType, size_t BlockSize>
		void PoolVector<ElementType, BlockSize>::Expand(size_t targetSize)
		{
			const size_t oldSize = mIndices.size();
			size_t realSize = ((targetSize + BlockSize - 1) / BlockSize) * BlockSize;
			mIndices.resize(realSize);

			for (size_t i = oldSize; i < realSize - 1; ++i)
			{
				const auto nextIndex = IndexType(i + 1);
				CPF_ASSERT(nextIndex == size_t(i + 1));  // Check for wrapping.
				Element freeElement;
				freeElement.mNextSlot = nextIndex;
				mIndices[i] = freeElement;
			}
			Element freeElement;
			freeElement.mNextSlot = IndexType(mFirstFree);
			mIndices[realSize - 1] = freeElement;
			mFirstFree = IndexType(oldSize);
		}
	}
}
