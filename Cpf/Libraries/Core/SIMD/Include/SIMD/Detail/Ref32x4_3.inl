//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2>
		constexpr Ref32x4_3<TYPE, I0, I1, I2>::operator typename TYPE::Lanes_3() const
		{
			return TYPE::Lanes_3(_Data()->GetLanes<I0, I1, I2>());
		}

		template <typename TYPE, int I0, int I1, int I2>
		typename TYPE::Element Ref32x4_3<TYPE, I0, I1, I2>::GetLane(int idx) const
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

			typename TYPE::Element GetLane(int idx) const { return _Data()->GetLane(idx); }

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
