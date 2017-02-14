//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Math.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"

namespace Cpf
{
	namespace Math
	{
		template<typename TYPE>
		class Quaternion;

		template<typename TYPE>
		class Matrix44v
		{
		public:
			using SimdType = TYPE;
			using ElementType = typename TYPE::ElementType;
			using RowType = Vector4v<TYPE>;

			Matrix44v();
			explicit Matrix44v(const ElementType* inData);
			Matrix44v(const Matrix44v<TYPE>& inMatrix);
			explicit Matrix44v(const RowType& r0, const RowType& r1, const RowType& r2, const RowType& r3);
			explicit Matrix44v(
				ElementType m00, ElementType m01, ElementType m02, ElementType m03,
				ElementType m10, ElementType m11, ElementType m12, ElementType m13,
				ElementType m20, ElementType m21, ElementType m22, ElementType m23,
				ElementType m30, ElementType m31, ElementType m32, ElementType m33);

			explicit Matrix44v(const Quaternionv<TYPE>& inQuat);

			RowType& operator [](int index);
			RowType operator [](int index) const;

			Matrix44v<TYPE>& operator =(const Matrix44v<TYPE>& inMatrix);
			Matrix44v<TYPE>& operator =(const ElementType* const inData);

			float* Data() { return reinterpret_cast<float*>(this); }
			const float* Data() const { return reinterpret_cast<const float*>(this); }

			static Matrix44v<TYPE> Identity();
			static Matrix44v<TYPE> Zero();

			static Matrix44v<TYPE> Scale(const ElementType x, const ElementType y, const ElementType z);
			static Matrix44v<TYPE> Scale(const Vector3v<SimdType>& inScales);
			static Matrix44v<TYPE> Translate(const ElementType x, const ElementType y, const ElementType z);
			static Matrix44v<TYPE> Translate(const Vector3v<SimdType>& inTranslation);
			static Matrix44v<TYPE> AxisAngle(const Vector3v<SimdType>& inAxis, const ElementType inAngle);
			static Matrix44v<TYPE> RotateX(const ElementType inAngle);
			static Matrix44v<TYPE> RotateY(const ElementType inAngle);
			static Matrix44v<TYPE> RotateZ(const ElementType inAngle);
			static Matrix44v<TYPE> Frustum(const ElementType l, const ElementType r, const ElementType b, const ElementType t, const ElementType n, const ElementType f);
			static Matrix44v<TYPE> Orthographic(const ElementType left, const ElementType right, const ElementType bottom, const ElementType top, const ElementType inNear, const ElementType inFar);
			static Matrix44v<TYPE> PerspectiveLH(ElementType w, ElementType h, ElementType zn, ElementType zf);
			static Matrix44v<TYPE> PerspectiveLH(ElementType w, ElementType h, ElementType zn, ElementType zf, ElementType dn, ElementType df);
			static Matrix44v<TYPE> PerspectiveOffCenterLH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf);
			static Matrix44v<TYPE> PerspectiveOffCenterLH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf, ElementType dn, ElementType df);
			static Matrix44v<TYPE> PerspectiveRH(ElementType w, ElementType h, ElementType zn, ElementType zf);
			static Matrix44v<TYPE> PerspectiveRH(ElementType w, ElementType h, ElementType zn, ElementType zf, ElementType dn, ElementType df);
			static Matrix44v<TYPE> PerspectiveOffCenterRH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf);
			static Matrix44v<TYPE> PerspectiveOffCenterRH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf, ElementType dn, ElementType df);
			static Matrix44v<TYPE> LookAt(const Vector3v<SimdType>& eye, const Vector3v<SimdType>& target, const Vector3v<SimdType>& up);

			template<typename T>
			friend Matrix44v<T> Transpose(const Matrix44v<T>& rhs);

			static RowType LinearCombination(RowType a, const Matrix44v<TYPE>& rhs)
			{
				RowType result;
				// TODO: This is direct Sse2, should be abstracted to something like:
				// result = a.xxxx * rhs.mRows[0];
				// result = result + a.yyyy * mRows[1];
				// result = result + a.zzzz * mRows[2];
				// result = result + a.wwww * mRows[3];
				result = _mm_mul_ps(_mm_shuffle_ps(a, a, 0x00), rhs.mRows[0]);
				result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0x55), rhs.mRows[1]));
				result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xaa), rhs.mRows[2]));
				result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xff), rhs.mRows[3]));
				return result;
			}

		private:
			RowType mRows[4];
		};

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v()
		{}

		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v(const ElementType* inData)
		{
			mRows[0] = RowType(inData[0], inData[1], inData[2], inData[3]);
			mRows[1] = RowType(inData[4], inData[5], inData[6], inData[7]);
			mRows[2] = RowType(inData[8], inData[9], inData[10], inData[11]);
			mRows[3] = RowType(inData[12], inData[13], inData[14], inData[15]);
		}

		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v(const Matrix44v<TYPE>& inMatrix)
		{
			mRows[0] = inMatrix.mRows[0];
			mRows[1] = inMatrix.mRows[1];
			mRows[2] = inMatrix.mRows[2];
			mRows[3] = inMatrix.mRows[3];
		}

		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v(const RowType& r0, const RowType& r1, const RowType& r2, const RowType& r3)
		{
			mRows[0] = r0;
			mRows[1] = r1;
			mRows[2] = r2;
			mRows[3] = r3;
		}


		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v(
			ElementType m00, ElementType m01, ElementType m02, ElementType m03,
			ElementType m10, ElementType m11, ElementType m12, ElementType m13,
			ElementType m20, ElementType m21, ElementType m22, ElementType m23,
			ElementType m30, ElementType m31, ElementType m32, ElementType m33)
		{
			mRows[0] = RowType(m00, m01, m02, m03);
			mRows[1] = RowType(m10, m11, m12, m13);
			mRows[2] = RowType(m20, m21, m22, m23);
			mRows[3] = RowType(m30, m31, m32, m33);
		}

		template<typename TYPE>
		Matrix44v<TYPE>::Matrix44v(const Quaternionv<TYPE>& inQuat)
		{
			const ElementType x = inQuat.x;
			const ElementType y = inQuat.y;
			const ElementType z = inQuat.z;
			const ElementType w = inQuat.w;

			const ElementType x2 = x + x;
			const ElementType y2 = y + y;
			const ElementType z2 = z + z;

			const ElementType xx = x2*x;
			const ElementType yy = y2*y;
			const ElementType zz = z2*z;

			const ElementType xy = x2*y;
			const ElementType xz = x2*z;
			const ElementType xw = x2*w;

			const ElementType yz = y2*z;
			const ElementType yw = y2*w;
			const ElementType zw = z2*w;

			mRows[0] = RowType(1.0f - yy - zz, xy + zw, xz - yw, 0.0f);
			mRows[1] = RowType(xy - zw, 1.0f - xx - zz, yz + xw, 0.0f);
			mRows[2] = RowType(xz + yw, yz - xw, 1.0f - xx - yy, 0.0f);
			mRows[3] = RowType(0.0f, 0.0f, 0.0f, 1.0f);
		}

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		typename Matrix44v<TYPE>::RowType& Matrix44v<TYPE>::operator [](int index)
		{
			return mRows[index];
		}

		template<typename TYPE>
		Vector4v<TYPE> Matrix44v<TYPE>::operator [](int index) const
		{
			return mRows[index];
		}

		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE>& Matrix44v<TYPE>::operator =(const Matrix44v<TYPE>& inMatrix)
		{
			mRows[0] = inMatrix[0];
			mRows[1] = inMatrix[1];
			mRows[2] = inMatrix[2];
			mRows[3] = inMatrix[3];
			return *this;
		}

		template<typename TYPE>
		Matrix44v<TYPE>& Matrix44v<TYPE>::operator =(const ElementType* const inData)
		{
			*this = Matrix44v<TYPE>(
				RowType(inData[0], inData[1], inData[2], inData[3]),
				RowType(inData[4], inData[5], inData[6], inData[7]),
				RowType(inData[8], inData[9], inData[10], inData[11]),
				RowType(inData[12], inData[13], inData[14], inData[15]));
			return *this;
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE> operator *(const Matrix44v<TYPE>& lhs, const Matrix44v<TYPE>& rhs)
		{
			Matrix44v<TYPE>	result = Matrix44v<TYPE>(
				Matrix44v<TYPE>::LinearCombination(lhs[0], rhs),
				Matrix44v<TYPE>::LinearCombination(lhs[1], rhs),
				Matrix44v<TYPE>::LinearCombination(lhs[2], rhs),
				Matrix44v<TYPE>::LinearCombination(lhs[3], rhs)
				);
			return result;
		}

		template<typename TYPE, typename RTYPE>
		Matrix44v<TYPE> operator *(const Matrix44v<TYPE>& lhs, RTYPE rhs)
		{
			Matrix44v<TYPE> result;
			for (int i = 0; i < 4; ++i)
				result[i] = lhs[i] * typename TYPE::ElementType(rhs);
			return result;
		}

		template<typename LTYPE, typename TYPE>
		Matrix44v<TYPE> operator *(LTYPE lhs, const Matrix44v<TYPE>& rhs)
		{
			return rhs * lhs;
		}

		template<typename TYPE, typename RTYPE>
		Matrix44v<TYPE> operator /(const Matrix44v<TYPE>& lhs, RTYPE rhs)
		{
			Matrix44v<TYPE> result;
			for (int i = 0; i < 4; ++i)
				result[i] = lhs[i] / typename TYPE::ElementType(rhs);
			return result;
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Identity()
		{
			return Matrix44v<TYPE>(
				RowType(1, 0, 0, 0),
				RowType(0, 1, 0, 0),
				RowType(0, 0, 1, 0),
				RowType(0, 0, 0, 1));
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Zero()
		{
			return Matrix44v<TYPE>(
				RowType(0),
				RowType(0),
				RowType(0),
				RowType(0));
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Scale(const ElementType x, const ElementType y, const ElementType z)
		{
			return Matrix44v<TYPE>(
				RowType(x, 0, 0, 0),
				RowType(0, y, 0, 0),
				RowType(0, 0, z, 0),
				RowType(0, 0, 0, 1)
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Scale(const Vector3v<SimdType>& inScales)
		{
			return Scale(inScales.X(), inScales.Y(), inScales.Z());
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Translate(const ElementType x, const ElementType y, const ElementType z)
		{
			return Matrix44v<TYPE>(
				RowType(1, 0, 0, 0),
				RowType(0, 1, 0, 0),
				RowType(0, 0, 1, 0),
				RowType(x, y, z, 1)
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Translate(const Vector3v<SimdType>& inTranslation)
		{
			return Translate(inTranslation.X(), inTranslation.Y(), inTranslation.Z());
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::AxisAngle(const Vector3v<SimdType>& inAxis, const ElementType inAngle)
		{
			CPF_ASSERT(MagnitudeSquared(inAxis) > ElementType(0.0001));
			Vector3v<SimdType> a = Normalize(inAxis);
			ElementType ca = std::cos(inAngle);
			ElementType sa = std::sin(inAngle);

			return Matrix44v<TYPE>(
				ca + a.x*a.x * (1 - ca),	a.y*a.x * (1 - ca) + a.z*sa,	a.z*a.x * (1 - ca) - a.y*sa,	0.0f,
				a.x*a.y*(1 - ca) - a.z*sa,	ca + a.y*a.y * (1 - ca),		a.z*a.y*(1 - ca) + a.x*sa,		0.0f,
				a.x*a.z*(1 - ca) + a.y*sa,	a.y*a.z*(1 - ca) - a.x*sa,		ca + a.z*a.z*(1 - ca),			0.0f,
				0.0f,						0.0f,							0.0f,							1.0f
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::RotateX(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix44v<TYPE>(
				1, 0, 0, 0,
				0, ca, sa, 0,
				0, -sa, ca, 0,
				0, 0, 0, 1
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::RotateY(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix44v<TYPE>(
				ca, 0, -sa, 0,
				0, 1, 0, 0,
				sa, 0, ca, 0,
				0, 0, 0, 1
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::RotateZ(const ElementType inAngle)
		{
			ElementType sa = std::sin(inAngle);
			ElementType ca = std::cos(inAngle);

			return Matrix44v<TYPE>(
				ca, sa, 0, 0,
				-sa, ca, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Frustum(const ElementType l, const ElementType r, const ElementType b, const ElementType t, const ElementType n, const ElementType f)
		{
			return Matrix44v<TYPE>(
				(2 * n) / (r - l), 0, 0, 0,
				0, (2 * n) / (t - b), 0, 0,
				(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
				0, 0, (-2 * f*n) / (f - n), 0);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::Orthographic(const ElementType left, const ElementType right, const ElementType bottom, const ElementType top, const ElementType inNear, const ElementType inFar)
		{
			const ElementType A = 2 / (right - left);
			const ElementType B = 2 / (top - bottom);
			const ElementType C = -2 / (inFar - inNear);
			const ElementType tx = -(right + left) / (right - left);
			const ElementType ty = -(top + bottom) / (top - bottom);
			const ElementType tz = -(inFar + inNear) / (inFar - inNear);

			return Matrix44v<TYPE>(
				A, 0, 0, 0,
				0, B, 0, 0,
				0, 0, C, 0,
				tx, ty, tz, 1);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveRH(ElementType w, ElementType h, ElementType zn, ElementType zf)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / w, 0, 0, 0,
				0, (2 * zn) / h, 0, 0,
				0, 0, -(zf + zn) / (zf - zn), -1,
				0, 0, -(2 * zf*zn) / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveRH(ElementType w, ElementType h, ElementType zn, ElementType zf, ElementType dn, ElementType df)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / w, 0, 0, 0,
				0, (2 * zn) / h, 0, 0,
				0, 0, (df*zf - dn*zn) / (zn - zf), -1,
				0, 0, (df - dn)*(zn*zf) / (zn - zf), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveOffCenterRH(typename Matrix44v<TYPE>::ElementType l, typename Matrix44v<TYPE>::ElementType r, typename Matrix44v<TYPE>::ElementType b, typename Matrix44v<TYPE>::ElementType t, typename Matrix44v<TYPE>::ElementType zn, typename Matrix44v<TYPE>::ElementType zf)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / (r - l), 0, 0, 0,
				0, (2 * zn) / (t - b), 0, 0,
				(r + l) / (r - l), (t + b) / (t - b), -(zf + zn) / (zf - zn), -1,
				0, 0, -(2 * zf*zn) / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveOffCenterRH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf, ElementType dn, ElementType df)
		{
			// see: https://anteru.net/blog/2011/12/27/1830/
			return Matrix44v<TYPE>(
				(2 * zn) / (r - l), 0, 0, 0,
				0, (2 * zn) / (t - b), 0, 0,
				(r + l) / (r - l), (t + b) / (t - b), -(df*zf - dn*zn) / (zn - zf), -1,
				0, 0, (df - dn)*(zn*zf) / (zn - zf), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveLH(ElementType w, ElementType h, ElementType zn, ElementType zf)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / w,	0,				0,						0,
				0,				(2 * zn) / h,	0,						0,
				0,				0,				zf / (zf - zn),			1,
				0,				0,				zn*zf / (zn - zf),		0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveLH(ElementType w, ElementType h, ElementType zn, ElementType zf, ElementType dn, ElementType df)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / w, 0, 0, 0,
				0, (2 * zn) / h, 0, 0,
				0, 0, (df*zf + dn*zn) / (zf - zn), 1,
				0, 0, -(df - dn)*(zn*zf) / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveOffCenterLH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / (r - l), 0, 0, 0,
				0, (2 * zn) / (t - b), 0, 0,
				(r + l) / (r - l), (t + b) / (t - b), zf + zn / (zf - zn), 1,
				0, 0, -zn*zf / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::PerspectiveOffCenterLH(ElementType l, ElementType r, ElementType b, ElementType t, ElementType zn, ElementType zf, ElementType dn, ElementType df)
		{
			return Matrix44v<TYPE>(
				(2 * zn) / (r - l), 0, 0, 0,
				0, (2 * zn) / (t - b), 0, 0,
				(r + l) / (r - l), (t + b) / (t - b), (df*zf + dn*zn) / (zf - zn), 1,
				0, 0, -(df - dn)*(zn*zf) / (zf - zn), 0
				);
		}

		template<typename TYPE>
		Matrix44v<TYPE> Matrix44v<TYPE>::LookAt(const Vector3v<SimdType>& eye, const Vector3v<SimdType>& target, const Vector3v<SimdType>& up)
		{
			Vector3v<SimdType> z = Normalize(target - eye);
			Vector3v<SimdType> x = Normalize(Cross(up, z));
			Vector3v<SimdType> y = Normalize(Cross(z, x));

			return Matrix44v<TYPE>(
				x.X(), y.X(), z.X(), 0,
				x.Y(), y.Y(), z.Y(), 0,
				x.Z(), y.Z(), z.Z(), 0,
				-Dot(x, eye), -Dot(y, eye), -Dot(z, eye), 1);
		}


		//////////////////////////////////////////////////////////////////////////
		template<typename TYPE>
		Matrix44v<TYPE> Transpose(const Matrix44v<TYPE>& rhs)
		{
			CPF_ASSERT_ALWAYS;
			return Matrix44v<TYPE>();
		}

		// TODO: This is experimental SIMD work..
		template<>
		inline Matrix44v<Simd::Float32x4> Transpose(const Matrix44v<Simd::Float32x4>& rhs)
		{
			using Type = Simd::Float32x4::ValueType;
			Matrix44v<Simd::Float32x4> result;
			Type tmp0, tmp1, tmp2, tmp3;

			tmp0 = Simd::Float32x4::SpliceLow(rhs.mRows[0], rhs.mRows[1]);
			tmp2 = Simd::Float32x4::SpliceLow(rhs.mRows[2], rhs.mRows[3]);
			tmp1 = Simd::Float32x4::SpliceHigh(rhs.mRows[0], rhs.mRows[1]);
			tmp3 = Simd::Float32x4::SpliceHigh(rhs.mRows[2], rhs.mRows[3]);
			result[0] = _mm_movelh_ps(tmp0, tmp2);
			result[1] = _mm_movehl_ps(tmp2, tmp0);
			result[2] = _mm_movelh_ps(tmp1, tmp3);
			result[3] = _mm_movehl_ps(tmp3, tmp1);

			return result;
		}

		template<typename TYPE>
		const float Determinant(const Matrix44v<TYPE>& m)
		{
			return(
				m[0][0] * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
					- m[2][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2])
					+ m[3][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]))
				-
				m[1][0] * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2])
					- m[2][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2])
					+ m[3][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2]))
				+
				m[2][0] * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2])
					- m[1][1] * (m[0][2] * m[3][3] - m[0][3] * m[3][2])
					+ m[3][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2]))
				-
				m[3][0] * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2])
					- m[1][1] * (m[0][2] * m[2][3] - m[0][3] * m[2][2])
					+ m[2][1] * (m[0][2] * m[1][3] - m[0][3] * m[1][2])));
		}

		template<typename TYPE>
		Matrix44v<TYPE> Invert(const Matrix44v<TYPE>& m)
		{
			using T = typename TYPE::ElementType;
			using Vector4 = typename Matrix44v<TYPE>::RowType;

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

			Vector4 Fac0(Coef00, Coef00, Coef02, Coef03);
			Vector4 Fac1(Coef04, Coef04, Coef06, Coef07);
			Vector4 Fac2(Coef08, Coef08, Coef10, Coef11);
			Vector4 Fac3(Coef12, Coef12, Coef14, Coef15);
			Vector4 Fac4(Coef16, Coef16, Coef18, Coef19);
			Vector4 Fac5(Coef20, Coef20, Coef22, Coef23);

			Vector4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			Vector4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			Vector4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			Vector4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			Vector4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			Vector4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			Vector4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			Vector4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			Vector4 SignA(+1, -1, +1, -1);
			Vector4 SignB(-1, +1, -1, +1);
			Matrix44v<TYPE> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			Vector4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			Vector4 Dot0(m[0] * Row0);
			T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			T OneOverDeterminant = static_cast<T>(1) / Dot1;

			return Inverse * OneOverDeterminant;
		}

		template<typename TYPE>
		Vector4v<TYPE> operator *(const Vector4v<TYPE>& lhs, const Matrix44v<TYPE>& rhs)
		{
			Vector4v<TYPE> result(
				lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0] + lhs[2] * rhs[2][0] + lhs[3] * rhs[3][0],
				lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1] + lhs[2] * rhs[2][1] + lhs[3] * rhs[3][1],
				lhs[0] * rhs[0][2] + lhs[1] * rhs[1][2] + lhs[2] * rhs[2][2] + lhs[3] * rhs[3][2],
				lhs[0] * rhs[0][3] + lhs[1] * rhs[1][3] + lhs[2] * rhs[2][3] + lhs[3] * rhs[3][3]
			);
			return result;
		}

		template<typename TYPE>
		Vector3v<TYPE> GetScale(const Matrix44v<TYPE>& m)
		{
			Vector3v<TYPE> x(m[0][0], m[1][0], m[2][0]);
			Vector3v<TYPE> y(m[0][1], m[1][1], m[2][1]);
			Vector3v<TYPE> z(m[0][2], m[1][2], m[2][2]);
			return Vector3v<TYPE>(Magnitude(x), Magnitude(y), Magnitude(z));
		}

		template<typename TYPE>
		Matrix33v<TYPE> GetOrientation(const Matrix44v<TYPE>& m)
		{
			Vector3v<TYPE> scales(GetScale(m));
			return Matrix33v<TYPE>(
				Vector3v<TYPE>(m[0].xyz) / scales.x,
				Vector3v<TYPE>(m[1].xyz) / scales.y,
				Vector3v<TYPE>(m[2].xyz) / scales.z
				);
		}

		template<typename TYPE>
		Vector3v<TYPE> GetTranslation(const Matrix44v<TYPE>& m)
		{
			return m[3].xyz;
		}
	}
}
