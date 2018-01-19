//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Move.hpp"

namespace CPF
{
	// TODO: Needs considerable cleanup.

	template <typename HANDLE_TYPE = uint64_t, size_t BLOCK_SIZE = 1024>
	class HandlePool
	{
	public:
		using Handle = HANDLE_TYPE;
		static constexpr Handle kInvalid = HANDLE_TYPE(0);
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
			d.mHandle = uint64_t(handle);
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

		Handle PredictHandle(size_t futureCount);

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
		uint32_t mUsed;
		Vector<HandleData> mHandles;
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	HandlePool<HANDLE_TYPE, BLOCK_SIZE>::HandlePool()
		: mFirstFree(kInvalidIndex)
		, mVersion(0)
		, mUsed(0)
	{
		_ReserveHandles(kHandleBlockSize);
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	HandlePool<HANDLE_TYPE, BLOCK_SIZE>::HandlePool(size_t size)
		: mFirstFree(kInvalidIndex)
		, mVersion(0)
		, mUsed(0)
	{
		_ReserveHandles(size);
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	HandlePool<HANDLE_TYPE, BLOCK_SIZE>::HandlePool(HandlePool&& rhs)
		: mFirstFree(rhs.mFirstFree)
		, mVersion(rhs.mVersion)
		, mUsed(rhs.mUsed)
		, mHandles(Move(rhs.mHandles))
	{
		rhs.mFirstFree = kInvalidIndex;
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	HandlePool<HANDLE_TYPE, BLOCK_SIZE>::~HandlePool()
	{
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	HandlePool<HANDLE_TYPE, BLOCK_SIZE>& HandlePool<HANDLE_TYPE, BLOCK_SIZE>::operator = (HandlePool&& rhs)
	{
		mFirstFree = rhs.mFirstFree;
		mHandles = Move(rhs.mHandles);
		mVersion = rhs.mVersion;
		mUsed = rhs.mUsed;
		rhs.mFirstFree = kInvalidIndex;
		return *this;
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	typename HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Handle HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Alloc(uint32_t index)
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

		++mUsed;
		return Handle(result.mHandle);
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	void HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Free(Handle which)
	{
		HandleData handle;
		handle.mHandle = which;
		CPF_ASSERT(handle.mVersion == mHandles[handle.mData].mVersion);
		--mUsed;
		_ReturnHandle(handle.mData);
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	uint32_t HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Get(Handle handle)
	{
		HandleData view;
		view.mHandle = uint64_t(handle);

		if (view.mVersion == mHandles[view.mData].mVersion)
			return mHandles[view.mData].mData;
		return kInvalidIndex;
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	size_t HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Size() const
	{
		return mHandles.size();
	}

	/*
	 * Predict the value of a handle allocated in the future.
	 * The prediction will only be valid if there are no free's
	 * called between the prediction and the given number of alloc
	 * calls are made.
	 */
	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	typename HandlePool<HANDLE_TYPE, BLOCK_SIZE>::Handle HandlePool<HANDLE_TYPE, BLOCK_SIZE>::PredictHandle(size_t futureCount)
	{
		const size_t available = mHandles.size() - size_t(mUsed);
		// Check if the request would end up allocating new handles.
		if (futureCount >= available)
		{
			const size_t delta = futureCount - available;
			HandleData view;
			view.mVersion = mVersion + uint32_t(available + delta) + 1;
			view.mData = uint32_t(mHandles.size() + delta);
			return Handle(view.mHandle);
		}

		size_t count = futureCount;
		uint32_t current = mFirstFree;
		while (count>0 && current!=kInvalidIndex)
		{
			current = mHandles[current].mData;
			--count;
		}
		size_t delta = futureCount - count;
		HandleData view;
		view.mVersion = uint32_t(mVersion + delta) + 1;
		view.mData = current;
		return Handle(view.mHandle);
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	void HandlePool<HANDLE_TYPE, BLOCK_SIZE>::_ReserveHandles(size_t size)
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

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	size_t HandlePool<HANDLE_TYPE, BLOCK_SIZE>::_AllocHandle()
	{
		if (mFirstFree == kInvalidIndex)
			_ReserveHandles(mHandles.size() + 1);

		const size_t result = size_t(mFirstFree);
		mHandles[result].mVersion = ++mVersion;
		mVersion = (mVersion == kInvalidIndex) ? 0 : mVersion;
		mFirstFree = mHandles[result].mData;
		return result;
	}

	template <typename HANDLE_TYPE, size_t BLOCK_SIZE>
	void HandlePool<HANDLE_TYPE, BLOCK_SIZE>::_ReturnHandle(size_t idx)
	{
		mHandles[idx].mData = mFirstFree;
		mHandles[idx].mVersion = kInvalidIndex;
		mFirstFree = uint32_t(idx);
	}
}
