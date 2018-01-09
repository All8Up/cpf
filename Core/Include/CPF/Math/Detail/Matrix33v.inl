//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Quaternion.hpp"
#include "CPF/Math/Trigonometric.hpp"

namespace CPF
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix33<TYPE>::Matrix33()
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(Element v0)
			: mRows{ Row(v0), Row(v0), Row(v0) }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(Row r0, Row r1, Row r2)
			: mRows{ r0, r1, r2 }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(
				Element _00, Element _01, Element _02,
				Element _10, Element _11, Element _12,
				Element _20, Element _21, Element _22
			)
			: mRows{ Row{ _00, _01, _02 }, Row{ _10, _11, _12 }, Row{ _20, _21, _22 } }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(Quaternion<typename TYPE::Lanes_4> value)
		{
			using T = Element;
			Element x2 = T(value.x) + T(value.x); Element y2 = T(value.y) + T(value.y);  Element z2 = T(value.z) + T(value.z);
			Element xx = T(value.x) * x2; Element xy = T(value.x) * y2;   Element xz = T(value.x) * z2;
			Element yy = T(value.y) * y2; Element yz = T(value.y) * z2;   Element zz = T(value.z) * z2;
			Element wx = T(value.w) * x2; Element wy = T(value.w) * y2;   Element wz = T(value.w) * z2;

			mRows[0] = Row(Element(1) - (yy + zz), xy + wz, xz - wy);
			mRows[1] = Row(xy - wz, Element(1) - (xx + zz), yz + wx);
			mRows[2] = Row(xz + wy, yz - wx, Element(1) - (xx + yy));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix33<TYPE>& CPF_VECTORCALL Matrix33<TYPE>::operator = (const Matrix33<TYPE>& rhs)
		{
			mRows[0] = rhs.mRows[0];
			mRows[1] = rhs.mRows[1];
			mRows[2] = rhs.mRows[2];
			return *this;
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Row& CPF_VECTORCALL Matrix33<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}
		template <typename TYPE>
		const typename Matrix33<TYPE>::Row& CPF_VECTORCALL Matrix33<TYPE>::operator [](int idx) const
		{
			return mRows[idx];
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL operator * (const Matrix33<TYPE>& lhs, const Matrix33<TYPE>& rhs)
		{
			Matrix33<TYPE> result(typename Matrix33<TYPE>::Element(0));
			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					for (int i = 0; i < 3; ++i)
						result[r][c] = result[r][c] + lhs[r][i] * rhs[i][c];
				}
			}
			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Identity()
		{
			return Matrix33<TYPE>(
				Element(1), Element(0), Element(0),
				Element(0), Element(1), Element(0),
				Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::AxisAngle(Row axis, Element radians)
		{
			CPF_ASSERT(MagnitudeSq(axis) > Element(0.0001));
			Row a = Normalize(axis);
			Element ca = Cos(radians);
			Element sa = Sin(radians);

			Element omc = 1 - ca;
			Element xx = a.x*a.x;
			Element xy = a.x*a.y;
			Element xz = a.x*a.z;
			Element yy = a.y*a.y;
			Element yz = a.y*a.z;
			Element zz = a.z*a.z;

			return Matrix33<TYPE>(
				ca + xx * omc, xy * omc + a.z * sa, xz * omc - a.y * sa,
				xy * omc - a.z * sa, ca + yy * omc, yz * omc + a.x * sa,
				xz * omc + a.y * sa, yz * omc - a.x * sa, ca + zz * omc
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationX(Element radians)
		{
			Element sa = Sin(radians);
			Element ca = Cos(radians);

			return Matrix33<TYPE>(
				1, 0, 0,
				0, ca, sa,
				0, -sa, ca
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationY(Element radians)
		{
			Element sa = Sin(radians);
			Element ca = Cos(radians);

			return Matrix33<TYPE>(
				ca, 0, -sa,
				0, 1, 0,
				sa, 0, ca
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationZ(Element radians)
		{
			Element sa = Sin(radians);
			Element ca = Cos(radians);

			return Matrix33<TYPE>(
				ca, sa, 0,
				-sa, ca, 0,
				0, 0, 1
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Scale(Element x, Element y)
		{
			using Element = typename TYPE::Element;
			return Matrix33<TYPE>(
				Element(x), Element(0), Element(0),
				Element(0), Element(y), Element(0),
				Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Translation(Element x, Element y)
		{
			using Element = typename TYPE::Element;
			return Matrix33<TYPE>(
				Element(1), Element(0), Element(0),
				Element(0), Element(1), Element(0),
				Element(x), Element(y), Element(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> CPF_VECTORCALL Transpose(const Matrix33<TYPE> value)
		{
			Matrix33<TYPE> result;
			for (int r = 0; r < 3; ++r)
			{
				typename Matrix33<TYPE>::Row column(value[0][r], value[1][r], value[2][r]);
				result[r] = column;
			}
			return result;
		}
		
		template <typename TYPE>
		typename Matrix33<TYPE>::Row GetXBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Row(
				value.mRows[0].x,
				value.mRows[1].x,
				value.mRows[2].x
			);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Row GetYBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Row(
				value.mRows[0].y,
				value.mRows[1].y,
				value.mRows[2].y
			);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Row GetZBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Row(
				value.mRows[0].z,
				value.mRows[1].z,
				value.mRows[2].z
			);
		}

		template <typename TYPE>
		bool CPF_VECTORCALL Near(const Matrix33<TYPE> lhs, const Matrix33<TYPE> rhs, typename Matrix33<TYPE>::Element tolerance)
		{
			return Near(lhs[0], rhs[0], tolerance) && Near(lhs[1], rhs[1], tolerance) && Near(lhs[2], rhs[2], tolerance);
		}
	}
}
