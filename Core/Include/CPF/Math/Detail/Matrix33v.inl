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
		Matrix33<TYPE>::Matrix33(LaneType v0)
			: mRows{ Vector3(v0), Vector3(v0), Vector3(v0) }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(Vector3 r0, Vector3 r1, Vector3 r2)
			: mRows{ r0, r1, r2 }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(
				LaneType _00, LaneType _01, LaneType _02,
				LaneType _10, LaneType _11, LaneType _12,
				LaneType _20, LaneType _21, LaneType _22
			)
			: mRows{ Vector3{ _00, _01, _02 }, Vector3{ _10, _11, _12 }, Vector3{ _20, _21, _22 } }
		{}

		template <typename TYPE>
		Matrix33<TYPE>::Matrix33(Quaternion<typename TYPE::Lanes_4> value)
		{
			using T = LaneType;
			LaneType x2 = T(value.x) + T(value.x); LaneType y2 = T(value.y) + T(value.y);  LaneType z2 = T(value.z) + T(value.z);
			LaneType xx = T(value.x) * x2; LaneType xy = T(value.x) * y2;   LaneType xz = T(value.x) * z2;
			LaneType yy = T(value.y) * y2; LaneType yz = T(value.y) * z2;   LaneType zz = T(value.z) * z2;
			LaneType wx = T(value.w) * x2; LaneType wy = T(value.w) * y2;   LaneType wz = T(value.w) * z2;

			mRows[0] = Vector3(LaneType(1) - (yy + zz), xy + wz, xz - wy);
			mRows[1] = Vector3(xy - wz, LaneType(1) - (xx + zz), yz + wx);
			mRows[2] = Vector3(xz + wy, yz - wx, LaneType(1) - (xx + yy));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix33<TYPE>& Matrix33<TYPE>::operator = (const Matrix33<TYPE>& rhs)
		{
			mRows[0] = rhs.mRows[0];
			mRows[1] = rhs.mRows[1];
			mRows[2] = rhs.mRows[2];
			return *this;
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Vector3& Matrix33<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}
		template <typename TYPE>
		const typename Matrix33<TYPE>::Vector3& Matrix33<TYPE>::operator [](int idx) const
		{
			return mRows[idx];
		}

		template <typename TYPE>
		Matrix33<TYPE> operator * (const Matrix33<TYPE>& lhs, const Matrix33<TYPE>& rhs)
		{
			Matrix33<TYPE> result(typename Matrix33<TYPE>::LaneType(0));
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

		template <typename TYPE>
		Vector3fv operator * (const Vector3fv& lhs, const Matrix33<TYPE>& rhs)
		{
			Vector3fv result(
				lhs.x * rhs.mRows[0].x + lhs.y * rhs.mRows[1].x + lhs.z * rhs.mRows[2].x,
				lhs.x * rhs.mRows[0].y + lhs.y * rhs.mRows[1].y + lhs.z * rhs.mRows[2].y,
				lhs.x * rhs.mRows[0].z + lhs.y * rhs.mRows[1].z + lhs.z * rhs.mRows[2].z
			);
			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::Identity()
		{
			return Matrix33<TYPE>(
				LaneType(1), LaneType(0), LaneType(0),
				LaneType(0), LaneType(1), LaneType(0),
				LaneType(0), LaneType(0), LaneType(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::AxisAngle(Vector3 axis, LaneType radians)
		{
			CPF_ASSERT(MagnitudeSq(axis) > LaneType(0.0001));
			Vector3 a = Normalize(axis);
			LaneType ca = Cos(radians);
			LaneType sa = Sin(radians);

			LaneType omc = 1 - ca;
			LaneType xx = a.x*a.x;
			LaneType xy = a.x*a.y;
			LaneType xz = a.x*a.z;
			LaneType yy = a.y*a.y;
			LaneType yz = a.y*a.z;
			LaneType zz = a.z*a.z;

			return Matrix33<TYPE>(
				ca + xx * omc, xy * omc + a.z * sa, xz * omc - a.y * sa,
				xy * omc - a.z * sa, ca + yy * omc, yz * omc + a.x * sa,
				xz * omc + a.y * sa, yz * omc - a.x * sa, ca + zz * omc
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::RotationX(LaneType radians)
		{
			LaneType sa = Sin(radians);
			LaneType ca = Cos(radians);

			return Matrix33<TYPE>(
				1, 0, 0,
				0, ca, sa,
				0, -sa, ca
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::RotationY(LaneType radians)
		{
			LaneType sa = Sin(radians);
			LaneType ca = Cos(radians);

			return Matrix33<TYPE>(
				ca, 0, -sa,
				0, 1, 0,
				sa, 0, ca
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::RotationZ(LaneType radians)
		{
			LaneType sa = Sin(radians);
			LaneType ca = Cos(radians);

			return Matrix33<TYPE>(
				ca, sa, 0,
				-sa, ca, 0,
				0, 0, 1
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::Scale(LaneType x, LaneType y)
		{
			using LaneType = typename TYPE::LaneType;
			return Matrix33<TYPE>(
				LaneType(x), LaneType(0), LaneType(0),
				LaneType(0), LaneType(y), LaneType(0),
				LaneType(0), LaneType(0), LaneType(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::Scale(LaneType x, LaneType y, LaneType z)
		{
			using LaneType = typename TYPE::LaneType;
			return Matrix33<TYPE>(
				LaneType(x), LaneType(0), LaneType(0),
				LaneType(0), LaneType(y), LaneType(0),
				LaneType(0), LaneType(0), LaneType(z)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Matrix33<TYPE>::Translation(LaneType x, LaneType y)
		{
			using LaneType = typename TYPE::LaneType;
			return Matrix33<TYPE>(
				LaneType(1), LaneType(0), LaneType(0),
				LaneType(0), LaneType(1), LaneType(0),
				LaneType(x), LaneType(y), LaneType(1)
				);
		}

		template <typename TYPE>
		Matrix33<TYPE> Transpose(const Matrix33<TYPE> value)
		{
			Matrix33<TYPE> result;
			for (int r = 0; r < 3; ++r)
			{
				typename Matrix33<TYPE>::Vector3 column(value[0][r], value[1][r], value[2][r]);
				result[r] = column;
			}
			return result;
		}

		template <typename TYPE>
		Vector2v<TYPE> GetScale2(const Matrix33<TYPE>& value)
		{
			return Vector2v<TYPE>(
				Magnitude(Vector2v<TYPE>(value.mRows[0].x, value.mRows[1].x)),
				Magnitude(Vector2v<TYPE>(value.mRows[0].y, value.mRows[1].y))
				);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Vector3 GetScale3(const Matrix33<TYPE>& value)
		{
			return typename Matrix33<TYPE>::Vector3(
				Magnitude(typename Matrix33<TYPE>::Vector3(value.mRows[0].x, value.mRows[1].x, value.mRows[2].x)),
				Magnitude(typename Matrix33<TYPE>::Vector3(value.mRows[0].y, value.mRows[1].y, value.mRows[2].y)),
				Magnitude(typename Matrix33<TYPE>::Vector3(value.mRows[0].z, value.mRows[1].z, value.mRows[2].z))
				);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Vector3 GetXBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Vector3(
				value.mRows[0].x,
				value.mRows[1].x,
				value.mRows[2].x
			);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Vector3 GetYBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Vector3(
				value.mRows[0].y,
				value.mRows[1].y,
				value.mRows[2].y
			);
		}

		template <typename TYPE>
		typename Matrix33<TYPE>::Vector3 GetZBasis(const Matrix33<TYPE> value)
		{
			return typename Matrix33<TYPE>::Vector3(
				value.mRows[0].z,
				value.mRows[1].z,
				value.mRows[2].z
			);
		}

		template <typename TYPE>
		bool Near(const Matrix33<TYPE> lhs, const Matrix33<TYPE> rhs, typename Matrix33<TYPE>::LaneType tolerance)
		{
			return Near(lhs[0], rhs[0], tolerance) && Near(lhs[1], rhs[1], tolerance) && Near(lhs[2], rhs[2], tolerance);
		}
	}
}
