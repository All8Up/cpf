//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"

namespace Cpf
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
			using Row = Vector3v<typename TYPE::Lanes_3>;
			using Element = typename Vector3v<TYPE>::Element;

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

#include "Math/Detail/Matrix33v.inl"
#include "SIMD/Types.hpp"

namespace Cpf
{
	namespace Math
	{
		using Matrix33fv = Matrix33<SIMD::F32x4>;
	}
}
