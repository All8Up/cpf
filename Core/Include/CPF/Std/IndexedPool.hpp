//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	// TODO: Needs considerable cleanup.

	template <typename TYPE, size_t BLOCK_SIZE = 64>
	class IndexedPool
	{
	public:
		using Handle = uint64_t;
		static constexpr Handle kInvalid = uint64_t(-1);
		static constexpr size_t kHandleBlockSize = BLOCK_SIZE;

		IndexedPool();
		IndexedPool(size_t size);
		IndexedPool(IndexedPool&& rhs);
		~IndexedPool();

		IndexedPool& operator = (IndexedPool&& rhs);

		Handle Alloc(TYPE&& item);
		void Free(Handle);

		TYPE* Get(Handle handle);

		size_t Size() const;

	private:
		IndexedPool(const IndexedPool&) = delete;
		IndexedPool& operator = (const IndexedPool&) = delete;

		void _ReserveHandles(size_t size);
		size_t _AllocHandle();
		void _ReturnHandle(size_t);

		static constexpr uint32_t kInvalidIndex = uint32_t(-1);
		union HandleStorage
		{
			struct
			{
				uint32_t mVersion;
				uint32_t mIndex;
			};
			uint64_t mHandle;
		};
		struct TypeStorage
		{
			TYPE mData;
			uint32_t mHandle;
		};

		uint32_t mFirstFree;
		uint32_t mVersion;
		Vector<HandleStorage> mHandles;
		Vector<TypeStorage> mData;
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename TYPE, size_t BLOCK_SIZE>
	IndexedPool<TYPE, BLOCK_SIZE>::IndexedPool()
		: mFirstFree(kInvalidIndex)
		, mVersion(0)
	{
		_ReserveHandles(kHandleBlockSize);
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	IndexedPool<TYPE, BLOCK_SIZE>::IndexedPool(size_t size)
		: mFirstFree(kInvalidIndex)
		, mData(size)
		, mVersion(0)
	{
		_ReserveHandles(size);
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	IndexedPool<TYPE, BLOCK_SIZE>::IndexedPool(IndexedPool&& rhs)
		: mFirstFree(rhs.mFirstFree)
		, mHandles(Move(rhs.mHandles))
		, mData(Move(rhs.mData))
		, mVersion(rhs.mVersion)
	{
		rhs.mFirstFree = kInvalidIndex;
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	IndexedPool<TYPE, BLOCK_SIZE>::~IndexedPool()
	{
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	IndexedPool<TYPE, BLOCK_SIZE>& IndexedPool<TYPE, BLOCK_SIZE>::operator = (IndexedPool&& rhs)
	{
		mFirstFree = rhs.mFirstFree;
		mHandles = Move(rhs.mHandles);
		mData = Move(rhs.mData);
		mVersion = rhs.mVersion;
		rhs.mFirstFree = kInvalidIndex;
		return *this;
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	typename IndexedPool<TYPE, BLOCK_SIZE>::Handle IndexedPool<TYPE, BLOCK_SIZE>::Alloc(TYPE&& item)
	{
		_ReserveHandles(mData.size()+1);

		auto index = mData.size();
		auto handleIndex = mFirstFree;

		mData.push_back({ Move(item), handleIndex });
		auto& handle = mHandles[handleIndex];

		mFirstFree = handle.mIndex;

		handle.mIndex = uint32_t(index);
		handle.mVersion = ++mVersion;
		if (mVersion == kInvalidIndex)
			mVersion = 0;

		HandleStorage result;
		result.mIndex = handleIndex;
		result.mVersion = handle.mVersion;
		return Handle(result.mHandle);
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	void IndexedPool<TYPE, BLOCK_SIZE>::Free(Handle which)
	{
		HandleStorage handle;
		handle.mHandle = which;
		CPF_ASSERT(handle.mVersion == mHandles[handle.mIndex].mVersion);

		if (handle.mIndex != uint32_t(mData.size()-1))
		{
			mHandles[mData.back().mHandle].mIndex = mHandles[handle.mIndex].mIndex;
			mData[mHandles[handle.mIndex].mIndex] = mData.back();
			mData.erase(mData.begin()+mData.size()-1);
		}
		_ReturnHandle(handle.mIndex);
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	TYPE* IndexedPool<TYPE, BLOCK_SIZE>::Get(Handle handle)
	{
		HandleStorage storage;
		storage.mHandle = handle;

		if (storage.mVersion == mHandles[storage.mIndex].mVersion)
			return &mData[mHandles[storage.mIndex].mIndex].mData;
		return nullptr;
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	size_t IndexedPool<TYPE, BLOCK_SIZE>::Size() const
	{
		return mData.size();
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	void IndexedPool<TYPE, BLOCK_SIZE>::_ReserveHandles(size_t size)
	{
		size_t blockCount = ((size - 1) / kHandleBlockSize) + 1;
		if (blockCount > mHandles.size() / kHandleBlockSize)
		{
			auto startIndex = mHandles.size();
			mHandles.resize(blockCount * kHandleBlockSize);
			auto iend = mHandles.end();

			int32_t i = int32_t(startIndex);
			for (auto ibegin = mHandles.begin() + startIndex; ibegin!=iend; ++ibegin)
			{
				auto& handle = *ibegin;
				handle.mVersion = kInvalidIndex;
				handle.mIndex = ++i;
			}
			mHandles.back().mIndex = kInvalidIndex;
			mFirstFree = int32_t(startIndex);
		}
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	size_t IndexedPool<TYPE, BLOCK_SIZE>::_AllocHandle()
	{
		if (mFirstFree == kInvalidIndex)
			_ReserveHandles(mHandles.size() + kHandleBlockSize);
		size_t result = size_t(mFirstFree);
		mHandles[result].mVersion = ++mVersion;
		mVersion = mVersion == kInvalidIndex ? 0 : mVersion;
		mFirstFree = mHandles[result].mIndex;
		return result;
	}

	template <typename TYPE, size_t BLOCK_SIZE>
	void IndexedPool<TYPE, BLOCK_SIZE>::_ReturnHandle(size_t idx)
	{
		mHandles[idx].mIndex = mFirstFree;
		mHandles[idx].mVersion = kInvalidIndex;
		mFirstFree = uint32_t(idx);
	}
}
