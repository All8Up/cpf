//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/HandleProvider.hpp"

namespace CPF
{
	namespace STD
	{
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE = 1024>
		class PackedPool
		{
		public:
			static_assert(sizeof(HANDLE_TYPE) == sizeof(uint64_t), "Handle type must be size of uint64_t.");
			static constexpr HANDLE_TYPE kInvalidHandle = HANDLE_TYPE(0);

			PackedPool();
			PackedPool(const PackedPool&) = default;
			PackedPool(PackedPool&&) = default;
			~PackedPool();

			PackedPool& operator =(const PackedPool&) = default;
			PackedPool& operator =(PackedPool&&) = default;

			HANDLE_TYPE Alloc(DATA_TYPE** data);

			HANDLE_TYPE Insert(const DATA_TYPE& data);
			HANDLE_TYPE Insert(DATA_TYPE&& data);

			bool Erase(HANDLE_TYPE handle);

			DATA_TYPE* Get(HANDLE_TYPE handle);
			const DATA_TYPE* Get(HANDLE_TYPE handle) const;

			size_t GetSize() const { return mData.size(); }

		private:
			static constexpr uint32_t kInvalidIndex = uint32_t(-1);

			uint32_t _GetNextIndex();
			void _FreeIndex(uint32_t index);
			void _ReserveIndexSlots(size_t size);

			using Provider = HandleProvider<HANDLE_TYPE, BLOCK_SIZE>;
			using IndexVector = Vector<uint32_t>;
			struct DataStorage
			{
				DATA_TYPE mData;
				size_t mSourceIndex;
			};
			using DataVector = Vector<DataStorage>;

			Provider mProvider;
			IndexVector mIndices;
			DataVector mData;
			size_t mNextIndex;
		};

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::PackedPool()
			: mNextIndex(kInvalidIndex)
		{
			_ReserveIndexSlots(BLOCK_SIZE);
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::~PackedPool()
		{}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Alloc(DATA_TYPE** data)
		{
			// Get the next available index slot.
			uint32_t indexSlot = _GetNextIndex();

			// Create a handle which points at the index slot.
			auto result = mProvider.Alloc(indexSlot);

			// Set the index slot to point at the soon to be filled in end of the data vector.
			mIndices[indexSlot] = uint32_t(mData.size());

			// Create a default data entry and set the output data pointer appropriately.
			mData.push_back({ DATA_TYPE(), indexSlot });
			if (data)
				data = &mData.back();

			// Return the handle.
			return result;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Insert(const DATA_TYPE& data)
		{
			uint32_t indexSlot = _GetNextIndex();
			auto result = mProvider.Alloc(indexSlot);
			mIndices[indexSlot] = uint32_t(mData.size());
			mData.push_back({ data, indexSlot });
			return result;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Insert(DATA_TYPE&& data)
		{
			uint32_t indexSlot = _GetNextIndex();
			auto result = mProvider.Alloc(indexSlot);
			mIndices[indexSlot] = uint32_t(mData.size());
			mData.push_back({ Move(data), indexSlot });
			return result;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		bool PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Erase(HANDLE_TYPE handle)
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);
				auto dataSlot = mIndices[indexSlot];

				if (dataSlot < mData.size() - 1)
				{
					mData[dataSlot] = Move(mData.back());
					mIndices[mData.back().mSourceIndex] = dataSlot;
					mData[dataSlot].mSourceIndex = indexSlot;
				}

				mData.pop_back();
				_FreeIndex(indexSlot);
				mProvider.Free(handle);
				return true;
			}
			return false;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		DATA_TYPE* PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Get(HANDLE_TYPE handle)
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);
				auto dataSlot = mIndices[indexSlot];
				return &mData[dataSlot].mData;
			}
			return nullptr;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		const DATA_TYPE* PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Get(HANDLE_TYPE handle) const
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);
				auto dataSlot = mIndices[indexSlot];
				return &mData[dataSlot].mData;
			}
			return nullptr;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		uint32_t PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::_GetNextIndex()
		{
			if (mNextIndex == kInvalidIndex)
				_ReserveIndexSlots(mIndices.size() + 1);
			const auto result = mNextIndex;
			CPF_ASSERT(result != kInvalidIndex);
			mNextIndex = mIndices[mNextIndex];
			return uint32_t(result);
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		void PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::_FreeIndex(uint32_t index)
		{
			mIndices[index] = uint32_t(mNextIndex);
			mNextIndex = index;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		void PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::_ReserveIndexSlots(size_t size)
		{
			const size_t blockCount = ((size - 1) / BLOCK_SIZE) + 1;
			if (blockCount > (mIndices.size() / BLOCK_SIZE))
			{
				const auto startIndex = mIndices.size();
				mIndices.resize(blockCount * BLOCK_SIZE);

				auto i = uint32_t(startIndex);
				const auto iend = mIndices.end();
				for (auto ibegin = mIndices.begin() + startIndex; ibegin != iend; ++ibegin)
				{
					auto& index = *ibegin;
					index = ++i;
				}
				mIndices.back() = kInvalidIndex;
				mNextIndex = uint32_t(startIndex);
			}
		}
	}
}
