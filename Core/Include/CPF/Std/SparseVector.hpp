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
			HANDLE_TYPE Insert(DATA_TYPE&& data)
			{
				auto result = mHandles.Alloc(uint32_t(mData.size()));
				mData.push_back({ uint32_t(mData.size()), Move(data) });
				return result;
			}
			void Erase(HANDLE_TYPE handle)
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

		private:
			HandleProvider<HANDLE_TYPE, BLOCK_SIZE> mHandles;
			using DataPair = Pair<uint32_t, DATA_TYPE>;
			using DataVector = Vector<DataPair>;
			DataVector mData;
		};
	}
}
