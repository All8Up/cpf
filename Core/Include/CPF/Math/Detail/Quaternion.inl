//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Quaternion<TYPE>::Quaternion()
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(typename TYPE::LaneType value)
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
		constexpr Quaternion<TYPE>::Quaternion(SIMD::LaneRef_4<TYPE, I0, I1, I2, I3>& ref)
			: mVector(ref)
		{}

		template <typename TYPE>
		Quaternion<TYPE>::Quaternion(typename TYPE::Lanes_3 v012, Element w)
			: mVector(v012, w)
		{}
		
		template<typename TYPE>
		template<typename MATRIX>
		Quaternion<TYPE>::Quaternion(const MATRIX& rhs)
		{
			float trace = rhs[0][0] + rhs[1][1] + rhs[2][2];

			if (trace > 0.001f)
			{
				float	s = 0.5f / ::sqrtf(trace + 1.0f);
				x = (rhs[1][2] - rhs[2][1]) * s;
				y = (rhs[2][0] - rhs[0][2]) * s;
				z = (rhs[0][1] - rhs[1][0]) * s;
				w = 0.25f / s;
			}
			else
			{
				if (rhs[0][0] > rhs[1][1] &&
					rhs[0][0] > rhs[2][2])
				{
					float	s = 2.0f * ::sqrtf(1.0f + rhs[0][0] - rhs[1][1] - rhs[2][2]);
					x = 0.25f * s;
					y = (rhs[1][0] + rhs[0][1]) / s;
					z = (rhs[2][0] + rhs[0][2]) / s;
					w = (rhs[1][2] - rhs[2][1]) / s;
				}
				else if (rhs[1][1] > rhs[2][2])
				{
					float	s = 2.0f * ::sqrtf(1.0f + rhs[1][1] - rhs[0][0] - rhs[2][2]);
					x = (rhs[1][0] + rhs[0][1]) / s;
					y = 0.25f * s;
					z = (rhs[2][1] + rhs[1][2]) / s;
					w = (rhs[2][0] - rhs[0][2]) / s;
				}
				else
				{
					float	s = 2.0f * ::sqrtf(1.0f + rhs[2][2] - rhs[0][0] - rhs[1][1]);
					x = (rhs[2][0] + rhs[0][2]) / s;
					y = (rhs[2][1] + rhs[1][2]) / s;
					z = 0.25f * s;
					w = (rhs[0][1] - rhs[1][0]) / s;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		SIMD::LaneIndex<TYPE> CPF_VECTORCALL Quaternion<TYPE>::operator [](int idx)
		{
			return SIMD::LaneIndex<TYPE>(mVector, idx);
		}

		template <typename TYPE>
		typename Quaternion<TYPE>::Element CPF_VECTORCALL Quaternion<TYPE>::operator [](int idx) const
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
		Quaternion<TYPE> CPF_VECTORCALL Conjugate(Quaternion<TYPE> value)
		{
			return Quaternion<TYPE>(-value.xyz, value.w);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Quaternion<TYPE> CPF_VECTORCALL operator * (const Quaternion<TYPE> lhs, const Quaternion<TYPE> rhs)
		{
			// TODO: This can be optimized.
			return Quaternion<TYPE>(
				+lhs[0] * rhs[3] + lhs[1] * rhs[2] - lhs[2] * rhs[1] + lhs[3] * rhs[0],
				-lhs[0] * rhs[2] + lhs[1] * rhs[3] + lhs[2] * rhs[0] + lhs[3] * rhs[1],
				+lhs[0] * rhs[1] - lhs[1] * rhs[0] + lhs[2] * rhs[3] + lhs[3] * rhs[2],
				-lhs[0] * rhs[0] - lhs[1] * rhs[1] - lhs[2] * rhs[2] + lhs[3] * rhs[3]
				);
		}
		
		template <typename TYPE>
		Vector3<typename TYPE::Lanes_3> CPF_VECTORCALL operator * (const Quaternion<TYPE>& lhs, const Vector3<typename TYPE::Lanes_3> rhs)
		{
			Vector3<typename TYPE::Lanes_3> u(lhs.xyz);
			typename Quaternion<TYPE>::Element s = lhs.w;
			return Vector3<typename TYPE::Lanes_3>(
				2 * Dot(u, rhs) * u +
				(s*s - Dot(u, u)) * rhs +
				2 * s * Cross(u, rhs)
			);
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Quaternion<TYPE> CPF_VECTORCALL Quaternion<TYPE>::Zero()
		{
			return Quaternion<TYPE>(Element(0), Element(0), Element(0), Element(0));
		}

		template <typename TYPE>
		Quaternion<TYPE> CPF_VECTORCALL Quaternion<TYPE>::Identity()
		{
			return Quaternion<TYPE>(Element(0), Element(0), Element(0), Element(1));
		}

		template <typename TYPE>
		template<typename ATYPE>
		Quaternion<TYPE> CPF_VECTORCALL Quaternion<TYPE>::AxisAngle(ATYPE axis, Element radians)
		{
			const float a = radians * Element(0.5);
			const float s = std::sin(a);
			return Quaternion<TYPE>(typename TYPE::Lanes_3(axis * s), std::cos(a));
		}

		template <typename TYPE>
		typename Quaternion<TYPE>::Element Dot(Quaternion<TYPE> lhs, Quaternion<TYPE> rhs)
		{
			return Dot(lhs.mVector, rhs.mVector);
		}

		template <typename TYPE>
		Quaternion<TYPE> CPF_VECTORCALL Normalize(const Quaternion<TYPE> value)
		{
		}

		template <typename TYPE>
		Quaternion<TYPE> CPF_VECTORCALL Inverse(const Quaternion<TYPE> value)
		{
			using Element = typename Quaternion<TYPE>::Element;
			Element lengthSq = Dot(value, value);
			if (lengthSq > Element(0))
			{
				Element invLength = Element(1) / lengthSq;
				Quaternion<TYPE> result = Conjugate(value) * invLength;
				return result;
			}
			return Quaternion<TYPE>(Element(0));
		}

		/*
		Lerp
		Slerp
		*/
	}
}
