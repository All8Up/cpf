//////////////////////////////////////////////////////////////////////////
#include "CPF/Std/HandleProvider.hpp"

namespace CPF
{
	namespace STD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE = 1024>
		class SparseVector
		{
		public:
			HANDLE_TYPE Insert(DATA_TYPE&& data);
			void Erase(HANDLE_TYPE handle);
			Option<DATA_TYPE*> operator [](HANDLE_TYPE handle);
			Option<const DATA_TYPE*> operator [](HANDLE_TYPE handle) const;

		private:
			using ProviderType = HandleProvider<HANDLE_TYPE, BLOCK_SIZE>;
			ProviderType mHandles;
			using DataPair = Pair<uint32_t, DATA_TYPE>;
			using DataVector = Vector<DataPair>;
			DataVector mData;
		};


		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		HANDLE_TYPE SparseVector<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Insert(DATA_TYPE&& data)
		{
			auto result = mHandles.Alloc(uint32_t(mData.size()));
			mData.push_back({ uint32_t(mData.size()), Move(data) });
			return result;
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		void SparseVector<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::Erase(HANDLE_TYPE handle)
		{
			auto index = mHandles.Get(handle);
			auto& data = mData[index];

			if (index < mData.size() - 1)
			{
				data = mData.back();
				mHandles.mHandles[mData.back().first].mData = index;
			}
			mData.pop_back();
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		Option<DATA_TYPE*> SparseVector<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::operator [](HANDLE_TYPE handle)
		{
			auto index = mHandles.Get(handle);
			if (index != ProviderType::kInvalidIndex)
			{
				return Option<DATA_TYPE*>::Some(&mData[index].second);
			}
			return Option<DATA_TYPE*>::None();
		}

		template <typename HANDLE_TYPE, typename DATA_TYPE, size_t BLOCK_SIZE>
		Option<const DATA_TYPE*> SparseVector<HANDLE_TYPE, DATA_TYPE, BLOCK_SIZE>::operator [](HANDLE_TYPE handle) const
		{
			auto index = mHandles.Get(handle);
			if (index != ProviderType::kInvalidIndex)
			{
				return Option<const DATA_TYPE*>::Some(&mData[index].second);
			}
			return Option<const DATA_TYPE*>::None();
		}
	}
}
