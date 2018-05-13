//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Pair.hpp"
#include "CPF/Std/HandleProvider.hpp"

namespace CPF
{
	namespace STD
	{
		/**
		 @brief A packed pod pool.  Handles are used such that the internal data can migrate
		 and maintain a continguous block of memory.
		 @tparam HANDLE_TYPE Type of the handle.  Must be 64 bits, generally you use an enum class to maintain type safety though.
		 @tparam DATA_TYPE Type of the data type.
		 @tparam BLOCK_SIZE Number of handles added on each grow, the internal data buffer uses std standard growth.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE = 1024>
		class PackedPool
		{
		public:
			static_assert(sizeof(HANDLE_TYPE) == sizeof(uint64_t), "Handle type must be size of uint64_t.");
			static constexpr HANDLE_TYPE kInvalidHandle = HANDLE_TYPE(0);

			using ValueType = Pair<HANDLE_TYPE, DATA_TYPE>;

			class iterator;
			class const_iterator;

			PackedPool() = default;
			PackedPool(const PackedPool&) = default;
			PackedPool(PackedPool&&) = default;
			~PackedPool() = default;

			PackedPool& operator =(const PackedPool&) = default;
			PackedPool& operator =(PackedPool&&) = default;

			HANDLE_TYPE Alloc(DATA_TYPE** data);

			HANDLE_TYPE Insert(const DATA_TYPE& data);
			HANDLE_TYPE Insert(DATA_TYPE&& data);

			bool Erase(HANDLE_TYPE handle);

			DATA_TYPE* Get(HANDLE_TYPE handle);
			const DATA_TYPE* Get(HANDLE_TYPE handle) const;

			size_t GetSize() const { return mData.size(); }

			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;

		private:
			using Provider = HandleProvider<HANDLE_TYPE, BLOCK_SIZE>;
			using DataVector = Vector<ValueType>;

			Provider mProvider;
			DataVector mData;
		};

		/**
		 @brief An iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		class PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::iterator
		{
		public:
			iterator() {}

			iterator operator ++(int) { iterator result = *this; ++mIt; return result; }
			iterator& operator ++() { ++mIt; return *this; }
			iterator operator --(int) { iterator result = *this; --mIt; return result; }
			iterator& operator --() { --mIt; return *this; }

			bool operator ==(const iterator& rhs) const { return mIt == rhs.mIt; }
			bool operator !=(const iterator& rhs) const { return mIt != rhs.mIt; }

			ValueType& operator*() const { return *mIt; }

		protected:
			iterator(typename DataVector::iterator it)
				: mIt(it)
			{}

		private:
			friend class PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>;

			typename DataVector::iterator mIt;
		};

		/**
		 @brief A constant iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		class PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::const_iterator
		{
		public:
			const_iterator() {}

			const_iterator operator ++(int) { const_iterator result = *this; ++mIt; return result; }
			const_iterator& operator ++() { ++mIt; return *this; }
			const_iterator operator --(int) { const_iterator result = *this; --mIt; return result; }
			const_iterator& operator --() { --mIt; return *this; }

			bool operator ==(const const_iterator& rhs) const { return mIt == rhs.mIt; }
			bool operator !=(const const_iterator& rhs) const { return mIt != rhs.mIt; }

			const ValueType& operator*() const { return *mIt; }

		protected:
			friend class PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>;

			const_iterator(typename DataVector::const_iterator it)
				: mIt(it)
			{}

		private:
			typename DataVector::const_iterator mIt;
		};


		/**
		 @brief Allocates a slot in the pool.
		 @param [in,out] data Output pointer to the new data area.
		 @return A HANDLE_TYPE.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Alloc(DATA_TYPE** data)
		{
			// Get the next available index slot.
			uint32_t indexSlot = uint32_t(mData.size());

			// Create a handle which points at the index slot.
			auto result = mProvider.Alloc(indexSlot);

			// Create a default data entry and set the output data pointer appropriately.
			mData.push_back({ result, DATA_TYPE() });
			if (data)
				*data = &mData.back().second;

			// Return the handle.
			return result;
		}

		/**
		 @brief Inserts a new record.
		 @param data The data.
		 @return A HANDLE_TYPE.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Insert(const DATA_TYPE& data)
		{
			uint32_t indexSlot = uint32_t(mData.size());
			auto result = mProvider.Alloc(indexSlot);
			mData.push_back({ result, data });
			return result;
		}

		/**
		 @brief Inserts a new record via move.
		 @param [in,out] data The data.
		 @return A HANDLE_TYPE.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Insert(DATA_TYPE&& data)
		{
			uint32_t indexSlot = uint32_t(mData.size());
			auto result = mProvider.Alloc(indexSlot);
			mData.push_back({ result, Move(data) });
			return result;
		}

		/**
		 @brief Erases the given handle and it's associated data.
		 @param handle The handle.
		 @return True if it succeeds, false if it fails.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		bool PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Erase(HANDLE_TYPE handle)
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);

				if (indexSlot < mData.size() - 1)
				{
					mData[indexSlot] = Move(mData.back());
					mProvider.Set(mData.back().first, indexSlot);
				}

				mData.pop_back();
				mProvider.Free(handle);
				return true;
			}
			return false;
		}

		/**
		 @brief Gets a pointer to the data referred to by the handle.
		 @param handle The handle.
		 @return Null if it fails, else a pointer to a DATA_TYPE.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		DATA_TYPE* PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Get(HANDLE_TYPE handle)
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);
				return &mData[indexSlot].second;
			}
			return nullptr;
		}

		/**
		 @brief Gets a pointer to the data referred to by the handle.
		 @param handle The handle.
		 @return Null if it fails, else a pointer to a const DATA_TYPE.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		const DATA_TYPE* PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Get(HANDLE_TYPE handle) const
		{
			if (mProvider.IsValid(handle))
			{
				auto indexSlot = mProvider.Get(handle);
				return &mData[indexSlot].second;
			}
			return nullptr;
		}

		/**
		 @brief Gets the begin iterator.
		 @return A PackedPool<HANDLE_TYPE,DATA_TYPE,BLOCK_SIZE>::iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		typename PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::iterator PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::begin()
		{
			return iterator(mData.begin());
		}

		/**
		 @brief Gets the const begin iterator.
		 @return A PackedPool<HANDLE_TYPE,DATA_TYPE,BLOCK_SIZE>::const_iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		typename PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::const_iterator PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::begin() const
		{
			return const_iterator(mData.begin());
		}

		/**
		 @brief Gets the end iterator.
		 @return A PackedPool<HANDLE_TYPE,DATA_TYPE,BLOCK_SIZE>::iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		typename PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::iterator PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::end()
		{
			return iterator(mData.end());
		}

		/**
		 @brief Gets the const end iterator.
		 @return A PackedPool<HANDLE_TYPE,DATA_TYPE,BLOCK_SIZE>::const_iterator.
		 */
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		typename PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::const_iterator PackedPool<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::end() const
		{
			return const_iterator(mData.end());
		}
	}
}
