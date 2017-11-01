//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"

namespace CPF
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
			using Element = typename TYPE::LaneType;

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

			// https://msdn.microsoft.com/en-us/library/windows/desktop/ee780369(v=vs.85).aspx
			static Matrix44<TYPE> CPF_VECTORCALL OrthographicLH(Element w, Element h, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL OrthographicRH(Element w, Element h, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL OrthographicOffCenterLH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL OrthographicOffCenterRH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveFovLH(Element fovy, Element aspect, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveFovRH(Element fovy, Element aspect, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveLH(Element w, Element h, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveRH(Element w, Element h, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterLH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element nzn, Element nzf);
			static Matrix44<TYPE> CPF_VECTORCALL PerspectiveOffCenterRH(Element l, Element r, Element b, Element t, Element zn, Element zf, Element nzn, Element nzf);

			static Matrix44<TYPE> CPF_VECTORCALL LookAt(const Vector3v<typename TYPE::Lanes_3> eye, const Vector3v<typename TYPE::Lanes_3> target, const Vector3v<typename TYPE::Lanes_3> up);

			//////////////////////////////////////////////////////////////////////////
			Row mRows[4];
		};
	}
}

#include "Math/Detail/Matrix44v.inl"
#include "SIMD/Types.hpp"

namespace CPF
{
	namespace Math
	{
		using Matrix44fv = Matrix44<SIMD::F32x4>;
		using Matrix44dv = Matrix44<SIMD::F64x4>;
	}
}
