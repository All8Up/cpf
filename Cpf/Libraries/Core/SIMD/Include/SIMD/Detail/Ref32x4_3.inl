//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2>
		constexpr Ref32x4_3<TYPE, I0, I1, I2>::operator typename TYPE::Lanes_3() const
		{
			return _Data()->template GetLanes<I0, I1, I2>();
		}

		template <typename TYPE, int I0, int I1, int I2>
		typename TYPE::LaneType Ref32x4_3<TYPE, I0, I1, I2>::GetLane(int idx) const
		{
			return _Data()->GetLane(idx);
		}


		template <typename TYPE, int I0, int I1, int I2>
		TYPE* Ref32x4_3<TYPE, I0, I1, I2>::_Data()
		{
			return reinterpret_cast<TYPE*>(mData);
		}

		template <typename TYPE, int I0, int I1, int I2>
		const TYPE* Ref32x4_3<TYPE, I0, I1, I2>::_Data() const
		{
			auto data = reinterpret_cast<const TYPE*>(mData);
			return data;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		class Ref32x4_3<TYPE, 0, 1, 2>
		{
		public:
			constexpr operator const typename TYPE::Lanes_3() const { return *reinterpret_cast<const typename TYPE::Lanes_3*>(_Data()); }

			typename TYPE::LaneType GetLane(int idx) const
			{
				switch (idx)
				{
				case 0: return _Data()->GetLane<0>();
				case 1: return _Data()->GetLane<1>();
				case 2: return _Data()->GetLane<2>();
				case 3: return _Data()->GetLane<3>();
				default: CPF_ASSERT_ALWAYS; return TYPE::LaneType(0);
				}
			}

		private:
			TYPE* _Data()
			{
				return reinterpret_cast<TYPE*>(mData);
			}
			const TYPE* _Data() const
			{
				auto data = reinterpret_cast<const TYPE*>(mData);
				return data;
			}

			uint8_t mData[1];
		};
	}
}
