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
			using LaneType = typename TYPE::LaneType;
			using Vector2 = Vector2v<typename TYPE::Lanes_2>;
			using Vector3 = Vector3<typename TYPE::Lanes_3>;

			//////////////////////////////////////////////////////////////////////////
			Matrix33();
			explicit Matrix33(LaneType v0);
			Matrix33(Vector3 r0, Vector3 r1, Vector3 r2);
			Matrix33(
				LaneType _00, LaneType _01, LaneType _02,
				LaneType _10, LaneType _11, LaneType _12,
				LaneType _20, LaneType _21, LaneType _22
				);
			explicit Matrix33(Quaternion<typename TYPE::Lanes_4> value);

			//////////////////////////////////////////////////////////////////////////
			Matrix33<TYPE>& operator = (const Matrix33<TYPE>& rhs);

			//////////////////////////////////////////////////////////////////////////
			Vector3& operator [](int idx);
			const Vector3& operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			static Matrix33<TYPE> Identity();
			static Matrix33<TYPE> AxisAngle(Vector3 axis, LaneType radians);
			static Matrix33<TYPE> RotationX(LaneType radians);
			static Matrix33<TYPE> RotationY(LaneType radians);
			static Matrix33<TYPE> RotationZ(LaneType radians);
			static Matrix33<TYPE> Scale(Vector2 scale) { return Scale(scale.x, scale.y); }
			static Matrix33<TYPE> Scale(LaneType x, LaneType y);
			static Matrix33<TYPE> Scale(Vector3 scale) { return Scale(scale.x, scale.y, scale.z); }
			static Matrix33<TYPE> Scale(LaneType x, LaneType y, LaneType z);
			static Matrix33<TYPE> Translation(LaneType x, LaneType y);

			//////////////////////////////////////////////////////////////////////////
			Vector3 mRows[3];
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
