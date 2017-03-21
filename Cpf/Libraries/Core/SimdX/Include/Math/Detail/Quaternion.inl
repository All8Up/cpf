//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Quaternion<TYPE>::Quaternion()
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(typename TYPE::Element value)
			: mVector(value)
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(TYPE value)
			: mVector(value)
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(Element v0, Element v1, Element v2, Element v3)
			: mVector(v0, v1, v2, v3)
		{}

		template <typename TYPE>
		template <int I0, int I1, int I2, int I3>
		constexpr Quaternion<TYPE>::Quaternion(Cpf::SIMD::Ref32x4_4<TYPE, I0, I1, I2, I3>& ref)
			: mVector(ref)
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(typename TYPE::Lanes_3 v012, Element w)
			: mVector(v012, w)
		{}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::Ref32x4_Index<TYPE> CPF_VECTORCALL Quaternion<TYPE>::operator [](int idx)
		{
			return SIMD::Ref32x4_Index<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		CPF_FORCE_INLINE typename Quaternion<TYPE>::Element CPF_VECTORCALL Quaternion<TYPE>::operator [](int idx) const
		{
			switch (idx)
			{
			case 0: return mVector.GetLane<0>();
			case 1: return mVector.GetLane<1>();
			case 2: return mVector.GetLane<2>();
			case 3: return mVector.GetLane<3>();
			}
			CPF_ASSERT_ALWAYS;
			return 0;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		CPF_FORCE_INLINE Quaternion<TYPE> CPF_VECTORCALL Conjugate(Quaternion<TYPE> value)
		{
			return Quaternion<TYPE>(-value.xyz, value.w);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Quaternion<TYPE> Quaternion<TYPE>::Identity()
		{
			return Quaternion<TYPE>(Element(0), Element(0), Element(0), Element(1));
		}

		template <typename TYPE>
		template<typename ATYPE>
		Quaternion<TYPE> CPF_VECTORCALL Quaternion<TYPE>::AxisAngle(ATYPE axis, Element radians)
		{
			const float a = radians * Element(0.5);
			const float s = std::sin(a);
			return Quaternion<TYPE>(axis * s, std::cos(a));
		}
	}
}
