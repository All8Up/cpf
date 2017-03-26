//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Quaternion;

		template <typename TYPE>
		struct Matrix44
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Row = Vector4v<TYPE>;
			using Element = typename TYPE::Element;

			//////////////////////////////////////////////////////////////////////////
			Matrix44();
			explicit Matrix44(Element v0);
			Matrix44(Row r0, Row r1, Row r2, Row r3);
			Matrix44(
				Element _00, Element _01, Element _02, Element _03,
				Element _10, Element _11, Element _12, Element _13,
				Element _20, Element _21, Element _22, Element _23,
				Element _30, Element _31, Element _32, Element _33
			);
			explicit Matrix44(Quaternion<typename TYPE::Lanes_4> value);

			//////////////////////////////////////////////////////////////////////////
			Matrix44<TYPE>& CPF_VECTORCALL operator = (const Matrix44<TYPE>& rhs);

			const Element* Data() const { return reinterpret_cast<const Element*>(this); }

			//////////////////////////////////////////////////////////////////////////
			Row& CPF_VECTORCALL operator [](int idx);
			const Row& CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			static Matrix44<TYPE> CPF_VECTORCALL Identity();
			static Matrix44<TYPE> CPF_VECTORCALL AxisAngle(Row axis, Element radians);
			static Matrix44<TYPE> CPF_VECTORCALL RotationX(Element radians);
			static Matrix44<TYPE> CPF_VECTORCALL RotationY(Element radians);
			static Matrix44<TYPE> CPF_VECTORCALL RotationZ(Element radians);
			static Matrix44<TYPE> CPF_VECTORCALL Scale(Element x, Element y, Element z);
			static Matrix44<TYPE> CPF_VECTORCALL Translation(Element x, Element y, Element z);

			static Matrix44<TYPE> CPF_VECTORCALL Frustum(const Element l, const Element r, const Element b, const Element t, const Element n, const Element f);
			static Matrix44<TYPE> CPF_VECTORCALL Orthographic(const Element left, const Element right, const Element bottom, const Element top, const Element inNear, const Element inFar);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveLH(Element w, Element h, Element zn, Element zf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveLH(Element w, Element h, Element zn, Element zf, Element dn, Element df);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterLH(Element l, Element r, Element b, Element t, Element zn, Element zf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterLH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element dn, Element df);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveRH(Element w, Element h, Element zn, Element zf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveRH(Element w, Element h, Element zn, Element zf, Element dn, Element df);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterRH(Element l, Element r, Element b, Element t, Element zn, Element zf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterRH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element dn, Element df);
			static Matrix44<TYPE> CPF_VECTORCALL LookAt(const Vector3v<typename TYPE::Lanes_3> eye, const Vector3v<typename TYPE::Lanes_3> target, const Vector3v<typename TYPE::Lanes_3> up);

			//////////////////////////////////////////////////////////////////////////
			Row mRows[4];
		};
	}
}

#include "Math/Detail/Matrix44v.inl"
#include "SIMD/Types.hpp"

namespace Cpf
{
	namespace Math
	{
		using Matrix44fv = Matrix44<SIMD::F32x4>;
	}
}
