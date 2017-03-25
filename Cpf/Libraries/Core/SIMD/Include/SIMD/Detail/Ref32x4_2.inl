//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace SIMD
	{
		template <typename TYPE, int I0, int I1>
		constexpr Ref32x4_2<TYPE, I0, I1>::operator typename TYPE::Lanes_2() const
		{
			return TYPE::Lanes_2(_Data()->GetLanes<I0, I1>());
		}

		template <typename TYPE, int I0, int I1>
		typename TYPE::Lanes_2* Ref32x4_2<TYPE, I0, I1>::_Data()
		{
			return reinterpret_cast<typename TYPE::Lanes_2*>(mData);
		}

		template <typename TYPE, int I0, int I1>
		const typename TYPE::Lanes_2* Ref32x4_2<TYPE, I0, I1>::_Data() const
		{
			return reinterpret_cast<const typename TYPE::Lanes_2*>(mData);
		}

		//////////////////////////////////////////////////////////////////////////
		// Unique special cases for optimization reasons.  0, 1 for instance is
		// just a direct copy without swizzle, 2, 3 could be accomplished with
		// a single movehl instruction etc.
		template <typename TYPE>
		class Ref32x4_2<TYPE, 0, 1>
		{
		public:
			constexpr operator typename TYPE::Lanes_2() const { return *_Data(); }

		private:
			typename TYPE::Lanes_2* _Data() { return reinterpret_cast<typename TYPE::Lanes_2*>(mData); }
			const typename TYPE::Lanes_2* _Data() const { return reinterpret_cast<const typename TYPE::Lanes_2*>(mData); }

			uint8_t mData[1];
		};
	}
}
