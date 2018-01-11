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

		Handle Alloc(uint32_t data);
		void Free(Handle);

		uint32_t Get(Handle handle);
		void Set(Handle handle, uint32_t data)
		{
			HandleData d;
			d.mHandle = handle;
			CPF_ASSERT(d.mVersion == mHandles[d.mData].mVersion);
			mHandles[d.mData].mData = data;
		}
		bool IsValid(Handle handle)
		{
			HandleData data;
			data.mHandle = handle;
			return mHandles[data.mData].mVersion == data.mVersion;
		}

		uint32_t GetVersion(Handle handle) const
		{
			HandleStorage storage; storage.mHandle = handle; return storage.mVersion;
		}
		uint32_t GetIndex(Handle handle) const
		{
			HandleStorage storage; storage.mHandle = handle; return storage.mData;
		}

		size_t Size() const;

	private:
		HandlePool(const HandlePool&) = delete;
		HandlePool& operator = (const HandlePool&) = delete;

		void _ReserveHandles(size_t size);
		size_t _AllocHandle();
		void _ReturnHandle(size_t);

		static constexpr uint32_t kInvalidIndex = uint32_t(-1);
		union HandleData
		{
			struct
			{
				uint32_t mVersion;
				uint32_t mData;
			};
			uint64_t mHandle;
		};

		uint32_t mFirstFree;
		uint32_t mVersion;
		Vector<HandleData> mHandles;
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

		// Unlink the first free handle.
		auto firstFree = mFirstFree;
		auto& handle = mHandles[mFirstFree];
		mFirstFree = handle.mData;

		// Set handle data.
		handle.mVersion = ++mVersion;
		handle.mData = index;

		// Check for version wrap, skip invalid if needed.
		if (mVersion == kInvalidIndex)
			mVersion = 0;

		// Prepare the result handle;
		HandleData result;
		result.mVersion = handle.mVersion;
		result.mData = firstFree;

		return Handle(result.mHandle);
	}

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::Free(Handle which)
	{
		HandleData handle;
		handle.mHandle = which;
		CPF_ASSERT(handle.mVersion == mHandles[handle.mData].mVersion);
		_ReturnHandle(handle.mData);
	}

	template <size_t BLOCK_SIZE>
	uint32_t HandlePool<BLOCK_SIZE>::Get(Handle handle)
	{
		HandleData view;
		view.mHandle = handle;

		if (view.mVersion == mHandles[view.mData].mVersion)
			return mHandles[view.mData].mData;
		return kInvalidIndex;
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
				handle.mData = ++i;
			}
			mHandles.back().mData = kInvalidIndex;
			mFirstFree = uint32_t(startIndex);
		}
	}

	template <size_t BLOCK_SIZE>
	size_t HandlePool<BLOCK_SIZE>::_AllocHandle()
	{
		if (mFirstFree == kInvalidIndex)
			_ReserveHandles(mHandles.size() + 1);

		const size_t result = size_t(mFirstFree);
		mHandles[result].mVersion = ++mVersion;
		mVersion = (mVersion == kInvalidIndex) ? 0 : mVersion;
		mFirstFree = mHandles[result].mData;
		return result;
	}

	template <size_t BLOCK_SIZE>
	void HandlePool<BLOCK_SIZE>::_ReturnHandle(size_t idx)
	{
		mHandles[idx].mData = mFirstFree;
		mHandles[idx].mVersion = kInvalidIndex;
		mFirstFree = uint32_t(idx);
	}
}
