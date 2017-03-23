//////////////////////////////////////////////////////////////////////////
#pragma once


namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1, int I2, int I3>
		TYPE* Ref32x4_4<TYPE, I0, I1, I2, I3>::_Data() { return reinterpret_cast<TYPE*>(mData); }

		template <typename TYPE, int I0, int I1, int I2, int I3>
		const TYPE* Ref32x4_4<TYPE, I0, I1, I2, I3>::_Data() const { return reinterpret_cast<const TYPE*>(mData); }

		template <typename TYPE, int I0, int I1, int I2, int I3>
		constexpr Ref32x4_4<TYPE, I0, I1, I2, I3>::operator typename TYPE::Lanes_4() const
		{
			return typename TYPE::F32x4_4(_mm_shuffle_ps(static_cast<__m128>(*_Data()), static_cast<__m128>(*_Data()), _MM_SHUFFLE(I3, I2, I1, I0)));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		class Ref32x4_4<TYPE, 0, 1, 2, 3>
		{
		public:
			constexpr operator typename TYPE::Lanes_4() const { return *_Data(); }

		private:
			TYPE* _Data() { return reinterpret_cast<TYPE*>(mData); }
			const TYPE* _Data() const { return reinterpret_cast<const TYPE*>(mData); }

			uint8_t mData[1];
		};
	}
}
