//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	// TODO: Needs considerable cleanup.

	template <size_t BLOCK_SIZE = 1024>
	class HandlePool
	{
	public:
		using Handle = uint64_t;
		static constexpr Handle kInvalid = uint64_t(0);
		static constexpr size_t kHandleBlockSize = BLOCK_SIZE;

		HandlePool();
		HandlePool(size_t size);
		HandlePool(HandlePool&& rhs);
		~HandlePool();

		HandlePool& operator = (HandlePool&& rhs);

		Handle Alloc(uint32_t index);
		void Free(Handle);

		uint32_t Get(Handle handle);
		void Set(Handle handle, uint32_t index);

		size_t Size() const;

	private:
		HandlePool(const HandlePool&) = delete;
		HandlePool& operator = (const HandlePool&) = delete;

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

		uint32_t mFirstFree;
		uint32_t mVersion;
		Vector<HandleStorage> mHandles;
	};

	//////////////////////////////////////////////////////////////////////////
	template <size_t BLOCK_SIZE>
	HandlePool<BLOCK_SIZE>::HandlePool()
		: mFirstFree(kInvalidIndex)
		, mVersion(0)
	{
		_ReserveHandles(kHandleBlockSize);
	}

	template <size_t BLOCK_SIZE>
	HandlePool<BLOCK_SIZE>::HandlePool(size_t size)
		: mFirstFree(kInvalidIndex)
		, mVersion(0)
	{
		_ReserveHandles(size);
	}

	template <size_t BLOCK_SIZE>
	HandlePool<BLOCK_SIZE>::HandlePool(HandlePool&& rhs)
		: mFirstFree(rhs.mFirstFree)
		, mVersion(rhs.mVersion)
		, mHandles(Move(rhs.mHandles))
	{
		rhs.mFirstFree = kInvalidIndex;
	}

	template <size_t BLOCK_SIZE>
	HandlePool<BLOCK_SIZE>::~HandlePool()
	{
	}

	template <size_t BLOCK_SIZE>
	HandlePool<BLOCK_SIZE>& HandlePool<BLOCK_SIZE>::operator = (HandlePool&& rhs)
	{
		mFirstFree = rhs.mFirstFree;
		mHandles = Move(rhs.mHandles);
		mVersion = rhs.mVersion;
		rhs.mFirstFree = kInvalidIndex;
		return *this;
	}

	template <size_t BLOCK_SIZE>
	typename HandlePool<BLOCK_SIZE>::Handle HandlePool<BLOCK_SIZE>::Alloc(uint32_t index)
	{
		if (mFirstFree==kInvalidIndex)
			_ReserveHandles(mHandles.size()+1);

		auto handleIndex = mFirstFree;
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

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::Free(Handle which)
	{
		HandleStorage handle;
		handle.mHandle = which;
		CPF_ASSERT(handle.mVersion == mHandles[handle.mIndex].mVersion);
		_ReturnHandle(handle.mIndex);
	}

	template <size_t BLOCK_SIZE>
	uint32_t HandlePool<BLOCK_SIZE>::Get(Handle handle)
	{
		HandleStorage storage;
		storage.mHandle = handle;

		if (storage.mVersion == mHandles[storage.mIndex].mVersion)
			return mHandles[storage.mIndex].mIndex;
		return kInvalidIndex;
	}

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::Set(Handle handle, uint32_t index)
	{
		HandleStorage storage;
		storage.mHandle = handle;

		if (storage.mVersion == mHandles[storage.mIndex].mVersion)
			mHandles[storage.mIndex].mIndex = index;
	}

	template <size_t BLOCK_SIZE>
	size_t HandlePool<BLOCK_SIZE>::Size() const
	{
		return mHandles.size();
	}

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::_ReserveHandles(size_t size)
	{
		size_t blockCount = ((size - 1) / kHandleBlockSize) + 1;
		if (blockCount > (mHandles.size() / kHandleBlockSize))
		{
			auto startIndex = mHandles.size();
			mHandles.resize(blockCount * kHandleBlockSize);

			uint32_t i = uint32_t(startIndex);
			auto iend = mHandles.end();
			for (auto ibegin = mHandles.begin() + startIndex; ibegin!=iend; ++ibegin)
			{
				auto& handle = *ibegin;
				handle.mVersion = kInvalidIndex;
				handle.mIndex = ++i;
			}
			mHandles.back().mIndex = kInvalidIndex;
			mFirstFree = uint32_t(startIndex);
		}
	}

	template <size_t BLOCK_SIZE>
	size_t HandlePool<BLOCK_SIZE>::_AllocHandle()
	{
		if (mFirstFree == kInvalidIndex)
			_ReserveHandles(mHandles.size() + 1);
		size_t result = size_t(mFirstFree);
		mHandles[result].mVersion = ++mVersion;
		mVersion = mVersion == kInvalidIndex ? 0 : mVersion;
		mFirstFree = mHandles[result].mIndex;
		return result;
	}

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::_ReturnHandle(size_t idx)
	{
		mHandles[idx].mIndex = mFirstFree;
		mHandles[idx].mVersion = kInvalidIndex;
		mFirstFree = uint32_t(idx);
	}
}
