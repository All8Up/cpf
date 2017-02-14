//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"


namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		class Quaternion;

		template<typename TYPE>
		class Matrix33v
		{
		public:
			using SimdType = TYPE;
			using ElementType = typename TYPE::ElementType;
			using RowType = Vector3v<TYPE>;

			Matrix33v();
			Matrix33v(const Matrix33v<TYPE>& inMatrix);

			explicit Matrix33v(const ElementType* inData);
			explicit Matrix33v(const RowType& r0, const RowType& r1, const RowType& r2);
			explicit Matrix33v(
				ElementType m00, ElementType m01, ElementType m02,
				ElementType m10, ElementType m11, ElementType m12,
				ElementType m20, ElementType m21, ElementType m22);

			explicit Matrix33v(const Quaternionv<TYPE>& inQuat);

			RowType& operator [](int index);
			const RowType operator [](int index) const;

			Matrix33v<TYPE>& operator =(const Matrix33v<TYPE>& inMatrix);

			Matrix33v<TYPE>& operator *=(const Matrix33v<TYPE>& inMatrix);
			Matrix33v<TYPE>& operator *=(const ElementType inScalar);
			Matrix33v<TYPE>& operator /=(const ElementType inScalar);

			static Matrix33v<TYPE> Identity();
			static Matrix33v<TYPE> Zero();

			static Matrix33v<TYPE> Scale(const ElementType x, const ElementType y);
			static Matrix33v<TYPE> Scale(const Vector2f& inScales);
			static Matrix33v<TYPE> Translate(const ElementType x, const ElementType y);
			static Matrix33v<TYPE> Translate(const Vector2f& inTranslation);

			static Matrix33v<TYPE> AxisAngle(const Vector3v<SimdType>& inAxis, const ElementType inAngle);
			static Matrix33v<TYPE> RotateX(const ElementType inAngle);
			static Matrix33v<TYPE> RotateY(const ElementType inAngle);
			static Matrix33v<TYPE> RotateZ(const ElementType inAngle);

			template<typename T>
			friend Matrix33v<T> Transpose(const Matrix33v<T>& rhs);
			template<typename T>
			friend Matrix33v<T> operator *(const Matrix33v<T>& lhs, const Matrix33v<T>& rhs);

		private:
			RowType mRows[3];
		};

		//////////////////////////////////////////////////////////////////////////
		using Matrix33fv = Matrix33v<Simd::Float32x4>;

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v()
		{}

		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v(const ElementType* inData)
		{
			mRows[0] = RowType(inData[0], inData[1], inData[2]);
			mRows[1] = RowType(inData[3], inData[4], inData[5]);
			mRows[2] = RowType(inData[6], inData[7], inData[8]);
		}

		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v(const Matrix33v<TYPE>& inMatrix)
		{
			mRows[0] = inMatrix.mRows[0];
			mRows[1] = inMatrix.mRows[1];
			mRows[2] = inMatrix.mRows[2];
		}

		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v(const RowType& r0, const RowType& r1, const RowType& r2)
		{
			mRows[0] = r0;
			mRows[1] = r1;
			mRows[2] = r2;
		}


		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v(
			ElementType m00, ElementType m01, ElementType m02,
			ElementType m10, ElementType m11, ElementType m12,
			ElementType m20, ElementType m21, ElementType m22)
		{
			mRows[0] = RowType(m00, m01, m02);
			mRows[1] = RowType(m10, m11, m12);
			mRows[2] = RowType(m20, m21, m22);
		}

		template<typename TYPE>
		Matrix33v<TYPE>::Matrix33v(const Quaternionv<TYPE>& q)
		{
			float x2 = q.x + q.x;  float y2 = q.y + q.y;  float z2 = q.z + q.z;
			float xx = q.x * x2;   float xy = q.x * y2;   float xz = q.x * z2;
			float yy = q.y * y2;   float yz = q.y * z2;   float zz = q.z * z2;
			float wx = q.w * x2;   float wy = q.w * y2;   float wz = q.w * z2;

			mRows[0] = Vector3fv(1.0f - (yy + zz), xy + wz, xz - wy);
			mRows[1] = Vector3fv(xy - wz, 1.0f - (xx + zz), yz + wx);
			mRows[2] = Vector3fv(xz + wy, yz - wx, 1.0f - (xx + yy));
		}

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		typename Matrix33v<TYPE>::RowType& Matrix33v<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}

		template<typename TYPE>
		const typename Matrix33v<TYPE>::RowType Matrix33v<TYPE>::operator [](int index) const
		{
			return mRows[index];
		}

		template<typename TYPE>
		Matrix33v<TYPE>& Matrix33v<TYPE>::operator =(const Matrix33v<TYPE>& inMatrix)
		{
			mRows[0] = inMatrix.mRows[0];
			mRows[1] = inMatrix.mRows[1];
			mRows[2] = inMatrix.mRows[2];

			return *this;
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix33v<TYPE> operator *(const Matrix33v<TYPE>& lhs, const Matrix33v<TYPE>& rhs)
		{
			Matrix33v<TYPE> result = Matrix33v<TYPE>::Zero();
			for (int r=0; r<3; ++r)
			{
				for (int c=0; c<3; ++c)
				{
					result.mRows[r].data[c] = typename Matrix33v<TYPE>::ElementType(0);
					for (int i = 0; i < 3; ++i)
						result.mRows[r].data[c] += lhs[r][i] * rhs[i][c];
				}
			}
			return result;
		}

		template<typename TYPE>
		Matrix33v<TYPE> operator *(const Matrix33v<TYPE>& lhs, typename TYPE::ElementType rhs)
		{
			Matrix33v<TYPE> result;
			for (int i = 0; i < 3; ++i)
				result[i] = lhs[i] * typename TYPE::ElementType(rhs);
			return result;
		}

		template<typename TYPE>
		Matrix33v<TYPE> operator *(typename TYPE::ElementType lhs, const Matrix33v<TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename TYPE>
		Matrix33v<TYPE> operator /(const Matrix33v<TYPE>& lhs, typename TYPE::ElementType rhs)
		{
			Matrix33v<TYPE> result;
			for (int i = 0; i < 3; ++i)
				result[i] = lhs[i] / typename TYPE::ElementType(rhs);
			return result;
		}

		template<typename TYPE>
		Vector3v<TYPE> operator *(const Vector3v<TYPE>& lhs, const Matrix33v<TYPE>& rhs)
		{
			Vector3v<TYPE> result(
				lhs.x * rhs[0][0] + lhs.y * rhs[1][0] + lhs.z * rhs[2][0],
				lhs.x * rhs[0][1] + lhs.y * rhs[1][1] + lhs.z * rhs[2][1],
				lhs.x * rhs[0][2] + lhs.y * rhs[1][2] + lhs.z * rhs[2][2]
				);
			return result;
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix33v<TYPE>& Matrix33v<TYPE>::operator *=(const Matrix33v<TYPE>& inMatrix)
		{
			*this = *this * inMatrix;
			return *this;
		}

		template<typename TYPE>
		Matrix33v<TYPE>& Matrix33v<TYPE>::operator *=(const ElementType inScalar)
		{
			*this = *this * inScalar;
			return *this;
		}

		template<typename TYPE>
		Matrix33v<TYPE>& Matrix33v<TYPE>::operator /=(const ElementType inScalar)
		{
			*this = *this / inScalar;
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Identity()
		{
			return Matrix33v<TYPE>(
				ElementType(1), ElementType(0), ElementType(0),
				ElementType(0), ElementType(1), ElementType(0),
				ElementType(0), ElementType(0), ElementType(1));
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Zero()
		{
			return Matrix33v<TYPE>(
				ElementType(0), ElementType(0), ElementType(0),
				ElementType(0), ElementType(0), ElementType(0),
				ElementType(0), ElementType(0), ElementType(0));
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Scale(const ElementType x, const ElementType y)
		{
			return Matrix33v<TYPE>(
				RowType(x, 0, 0),
				RowType(0, y, 0),
				RowType(0, 0, 1)
				);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Scale(const Vector2f& inScales)
		{
			return Scale(inScales.x, inScales.y);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Translate(const ElementType x, const ElementType y)
		{
			return Matrix33v<TYPE>(
				RowType(1, 0, 0),
				RowType(0, 1, 0),
				RowType(x, y, 1)
				);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::Translate(const Vector2f& inTranslation)
		{
			return Translate(inTranslation.x, inTranslation.y);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::AxisAngle(const Vector3v<SimdType>& inAxis, const ElementType inAngle)
		{
			CPF_ASSERT(MagnitudeSquared(inAxis) > ElementType(0.0001));
			Vector3v<SimdType> a = Normalize(inAxis);
			ElementType ca = std::cos(inAngle);
			ElementType sa = std::sin(inAngle);

			ElementType omc = 1 - ca;
			ElementType xx = a.x*a.x;
			ElementType xy = a.x*a.y;
			ElementType xz = a.x*a.z;
			ElementType yy = a.y*a.y;
			ElementType yz = a.y*a.z;
			ElementType zz = a.z*a.z;

			return Matrix33v<TYPE>(
				ca + xx * omc,			xy * omc + a.z * sa,	xz * omc - a.y * sa,
				xy * omc - a.z * sa,	ca + yy * omc,			yz * omc + a.x * sa,
				xz * omc + a.y * sa,	yz * omc - a.x * sa,	ca + zz * omc
				);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::RotateX(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix33v<TYPE>(
				1, 0, 0,
				0, ca, sa,
				0, -sa, ca
			);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::RotateY(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix33v<TYPE>(
				ca, 0, -sa,
				0, 1, 0,
				sa, 0, ca
			);
		}

		template<typename TYPE>
		Matrix33v<TYPE> Matrix33v<TYPE>::RotateZ(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix33v<TYPE>(
				ca, sa, 0,
				-sa, ca, 0,
				0, 0, 1
			);
		}

		template<typename T>
		Matrix33v<T> Transpose(const Matrix33v<T>& rhs)
		{
			Matrix33v<T> result;
			for (int r = 0; r < 3; ++r)
			{
				Vector3v<T> column = Vector3fv(rhs[0][r], rhs[1][r], rhs[2][r]);
				result[r] = column;
			}
			return result;
		}
	}
}
