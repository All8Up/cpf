//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Quaternion.hpp"
#include "Math/Constants.hpp"

namespace CPF
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> inline
			Matrix44<TYPE>::Matrix44()
		{}

		template <typename TYPE> inline
			Matrix44<TYPE>::Matrix44(Element v0)
			: mRows{ Row(v0), Row(v0), Row(v0), Row(v0) }
		{}

		template <typename TYPE> inline
			Matrix44<TYPE>::Matrix44(Row r0, Row r1, Row r2, Row r3)
			: mRows{ r0, r1, r2, r3 }
		{}

		template <typename TYPE> inline
			Matrix44<TYPE>::Matrix44(
				Element _00, Element _01, Element _02, Element _03,
				Element _10, Element _11, Element _12, Element _13,
				Element _20, Element _21, Element _22, Element _23,
				Element _30, Element _31, Element _32, Element _33
			)
			: mRows{ Row{ _00, _01, _02, _03 }, Row{ _10, _11, _12, _13 }, Row{ _20, _21, _22, _23 }, Row{ _30, _31, _32, _33 } }
		{}

		template <typename TYPE> inline
			Matrix44<TYPE>::Matrix44(Quaternion<typename TYPE::Lanes_4> value)
		{
			Element x2 = value.x + value.x; Element y2 = value.y + value.y; Element z2 = value.z + value.z;
			Element xx = value.x * x2;   	Element xy = value.x * y2;   	Element xz = value.x * z2;
			Element yy = value.y * y2;   	Element yz = value.y * z2;   	Element zz = value.z * z2;
			Element wx = value.w * x2;   	Element wy = value.w * y2;   	Element wz = value.w * z2;

			mRows[0] = Row(Element(1) - (yy + zz), xy + wz, xz - wy, Element(0));
			mRows[1] = Row(xy - wz, Element(1) - (xx + zz), yz + wx, Element(0));
			mRows[2] = Row(xz + wy, yz - wx, Element(1) - (xx + yy), Element(0));
			mRows[3] = Row(Element(0), Element(0), Element(0), Element(1));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> inline
			Matrix44<TYPE>& CPF_VECTORCALL Matrix44<TYPE>::operator = (const Matrix44<TYPE>& rhs)
		{
			mRows[0] = rhs.mRows[0];
			mRows[1] = rhs.mRows[1];
			mRows[2] = rhs.mRows[2];
			mRows[3] = rhs.mRows[3];
			return *this;
		}

		template <typename TYPE> inline
			typename Matrix44<TYPE>::Row& CPF_VECTORCALL Matrix44<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}

		template <typename TYPE> inline
			const typename Matrix44<TYPE>::Row& CPF_VECTORCALL Matrix44<TYPE>::operator [](int idx) const
		{
			return mRows[idx];
		}

		template <typename TYPE>
		Matrix44<TYPE> CPF_VECTORCALL operator * (const Matrix44<TYPE>& lhs, const Matrix44<TYPE>& rhs)
		{
			Matrix44<TYPE> result(typename Matrix44<TYPE>::Element(0));
			for (int r = 0; r < 4; ++r)
			{
				for (int c = 0; c < 4; ++c)
				{
					for (int i = 0; i < 4; ++i)
						result[r][c] = result[r][c] + lhs[r][i] * rhs[i][c];
				}
			}
			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::Identity()
		{
			return Matrix44<TYPE>(
				Element(1), Element(0), Element(0), Element(0),
				Element(0), Element(1), Element(0), Element(0),
				Element(0), Element(0), Element(1), Element(0),
				Element(0), Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::AxisAngle(Row axis, Element radians)
		{
			CPF_ASSERT(MagnitudeSq(axis) > Element(0.0001));
			Row a = Normalize(axis);
			Element ca = std::cos(radians);
			Element sa = std::sin(radians);

			Element omc = 1 - ca;
			Element xx = a.x*a.x;
			Element xy = a.x*a.y;
			Element xz = a.x*a.z;
			Element yy = a.y*a.y;
			Element yz = a.y*a.z;
			Element zz = a.z*a.z;

			return Matrix44<TYPE>(
				ca + xx * omc, xy * omc + a.z * sa, xz * omc - a.y * sa, Element(0),
				xy * omc - a.z * sa, ca + yy * omc, yz * omc + a.x * sa, Element(0),
				xz * omc + a.y * sa, yz * omc - a.x * sa, ca + zz * omc, Element(0),
				Element(0), Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::RotationX(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix44<TYPE>(
				1, 0, 0, 0,
				0, ca, sa, 0,
				0, -sa, ca, 0,
				0, 0, 0, 1
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::RotationY(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix44<TYPE>(
				ca, 0, -sa, 0,
				0, 1, 0, 0,
				sa, 0, ca, 0,
				0, 0, 0, 1
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::RotationZ(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix44<TYPE>(
				ca, sa, 0, 0,
				-sa, ca, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::Scale(Element x, Element y, Element z)
		{
			using Element = typename TYPE::Element;
			return Matrix44<TYPE>(
				Element(x), Element(0), Element(0), Element(0),
				Element(0), Element(y), Element(0), Element(0),
				Element(0), Element(0), Element(z), Element(0),
				Element(0), Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::Translation(Element x, Element y, Element z)
		{
			using Element = typename TYPE::Element;
			return Matrix44<TYPE>(
				Element(1), Element(0), Element(0), Element(0),
				Element(0), Element(1), Element(0), Element(0),
				Element(0), Element(0), Element(1), Element(0),
				Element(x), Element(y), Element(z), Element(1)
				);
		}

		template <typename TYPE> inline
			Matrix44<TYPE> CPF_VECTORCALL Transpose(const Matrix44<TYPE> value)
		{
			Matrix44<TYPE> result;
			for (int r = 0; r < 4; ++r)
			{
				typename Matrix44<TYPE>::Row column(value[0][r], value[1][r], value[2][r], value[3][r]);
				result[r] = column;
			}
			return result;
		}

		template<typename TYPE>
		Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::PerspectiveLH(Element w, Element h, Element zn, Element zf, Element nzn, Element nzf)
		{
			return Matrix44<TYPE>(
				(2 * zn) / w, 0, 0, 0,
				0, (2 * zn) / h, 0, 0,
				0, 0, (nzf*zf + nzn*zn) / (zf - zn), 1,
				0, 0, -(nzf - nzn)*(zn*zf) / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::PerspectiveFovLH(Element fovy, Element aspect, Element zn, Element zf, Element nzn, Element nzf)
		{
			Element h = Element(1) / std::tan(fovy*Element(0.5));
			Element w = h / aspect;
			return Matrix44<TYPE>(
				w, 0, 0, 0,
				0, h, 0, 0,
				0, 0, (nzf*zf + nzn*zn) / (zf - zn), 1,
				0, 0, -(nzf - nzn)*(zn*zf) / (zf - zn), 0
				);
		}


		template<typename TYPE>
		Matrix44<TYPE> CPF_VECTORCALL Matrix44<TYPE>::LookAt(const Vector3v<typename TYPE::Lanes_3> eye, const Vector3v<typename TYPE::Lanes_3> target, const Vector3v<typename TYPE::Lanes_3> up)
		{
			Vector3v<typename TYPE::Lanes_3> z = Normalize(target - eye);
			Vector3v<typename TYPE::Lanes_3> x = Normalize(Cross(up, z));
			Vector3v<typename TYPE::Lanes_3> y = Normalize(Cross(z, x));

			return Matrix44<TYPE>(
				x.x, y.x, z.x, 0,
				x.y, y.y, z.y, 0,
				x.z, y.z, z.z, 0,
				-Dot(x, eye), -Dot(y, eye), -Dot(z, eye), 1);
		}

		template<typename TYPE>
		Matrix44<TYPE> CPF_VECTORCALL Inverse(const Matrix44<TYPE>& m)
		{
			using T = typename TYPE::Element;
			using Row = typename Matrix44<TYPE>::Row;

			T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			Row Fac0(Coef00, Coef00, Coef02, Coef03);
			Row Fac1(Coef04, Coef04, Coef06, Coef07);
			Row Fac2(Coef08, Coef08, Coef10, Coef11);
			Row Fac3(Coef12, Coef12, Coef14, Coef15);
			Row Fac4(Coef16, Coef16, Coef18, Coef19);
			Row Fac5(Coef20, Coef20, Coef22, Coef23);

			Row Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			Row Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			Row Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			Row Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			Row Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			Row Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			Row Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			Row Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			Row SignA(+1, -1, +1, -1);
			Row SignB(-1, +1, -1, +1);
			Matrix44<TYPE> inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			Row Row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

			Row Dot0(m[0] * Row0);
			T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			T oneOverDeterminant = T(1) / Dot1;

			return inverse * oneOverDeterminant;
		}

		template <typename TYPE> inline
			bool CPF_VECTORCALL Near(const Matrix44<TYPE> lhs, const Matrix44<TYPE> rhs, typename Matrix44<TYPE>::Element tolerance)
		{
			return Near(lhs[0], rhs[0], tolerance) && Near(lhs[1], rhs[1], tolerance)
				&& Near(lhs[2], rhs[2], tolerance) && Near(lhs[3], rhs[3], tolerance);
		}
	}
}
