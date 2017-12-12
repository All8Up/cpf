//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		union Quaternion;

		template <typename TYPE>
		struct Matrix33
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Row = Vector3<typename TYPE::Lanes_3>;
			using Element = typename Vector3<TYPE>::LaneType;

			//////////////////////////////////////////////////////////////////////////
			Matrix33();
			explicit Matrix33(Element v0);
			Matrix33(Row r0, Row r1, Row r2);
			Matrix33(
				Element _00, Element _01, Element _02,
				Element _10, Element _11, Element _12,
				Element _20, Element _21, Element _22
				);
			explicit Matrix33(Quaternion<typename TYPE::Lanes_4> value);

			//////////////////////////////////////////////////////////////////////////
			Matrix33<TYPE>& CPF_VECTORCALL operator = (const Matrix33<TYPE>& rhs);

			//////////////////////////////////////////////////////////////////////////
			Row& CPF_VECTORCALL operator [](int idx);
			const Row& CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			static Matrix33<TYPE> CPF_VECTORCALL Identity();
			static Matrix33<TYPE> CPF_VECTORCALL AxisAngle(Row axis, Element radians);
			static Matrix33<TYPE> CPF_VECTORCALL RotationX(Element radians);
			static Matrix33<TYPE> CPF_VECTORCALL RotationY(Element radians);
			static Matrix33<TYPE> CPF_VECTORCALL RotationZ(Element radians);
			static Matrix33<TYPE> CPF_VECTORCALL Scale(Element x, Element y);
			static Matrix33<TYPE> CPF_VECTORCALL Translation(Element x, Element y);

			//////////////////////////////////////////////////////////////////////////
			Row mRows[3];
		};
	}
}

#include "CPF/Math/Detail/Matrix33v.inl"
#include "CPF/SIMD/Types.hpp"

namespace CPF
{
	namespace Math
	{
		using Matrix33fv = Matrix33<SIMD::F32x4>;
		using Matrix33dv = Matrix33<SIMD::F64x4>;
	}
}
