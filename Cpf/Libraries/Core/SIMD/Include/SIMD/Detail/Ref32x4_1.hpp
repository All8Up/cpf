//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace SIMD
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE, int INDEX>
		class Ref32x4_1
		{
		public:
			using Element = typename TYPE::Element;

			Ref32x4_1& operator = (Element value);
			operator Element() const;

		private:
			TYPE* _Data();
			const TYPE* _Data() const;

			uint8_t mData[1];
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		class Ref32x4_Index
		{
		public:
			using Element = typename TYPE::Element;

			Ref32x4_Index(TYPE& v, int idx);
			Ref32x4_Index(const Ref32x4_Index& rhs);

			Ref32x4_Index& operator = (Element value);
			operator Element() const;

		private:
			TYPE& mVector;
			const int mIndex;
		};
	}
}

#include "Ref32x4_1.inl"

#define REF32X4_1_SWIZZLE(t)		\
	Cpf::SIMD::Ref32x4_1<t, 0> x;	\
	Cpf::SIMD::Ref32x4_1<t, 1> y;	\
	Cpf::SIMD::Ref32x4_1<t, 2> z;	\
	Cpf::SIMD::Ref32x4_1<t, 3> w;
