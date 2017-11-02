//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector3v.hpp"
#include "Math/Matrix44v.hpp"
#include "Math/Quaternion.hpp"

namespace CPF
{
	namespace Math
	{
		/** @brief Transform data. */
		class Transform
		{
		public:
#define USE_SIMD 0
#define DOUBLE_TRANSFORM 1
#if DOUBLE_TRANSFORM
#	if USE_SIMD
			using Real = double;
			using Quat = Quaterniond;
			using Vector3 = Vector3dv;
			using Matrix44 = Matrix44dv;
#	else
			using Real = double;
			using Quat = Quaternion<SIMD::Reference::F64x4_4>;
			using Vector3 = Math::Vector3v<SIMD::Reference::F64x4_3>;
			using Matrix44 = Matrix44<SIMD::Reference::F64x4_4>;
#	endif
#else
			using Real = float;
			using Quaternion = Quaternionf;
			using Vector3 = Vector3fv;
			using Matrix44 = Matrix44fv;
#endif

			// Construction.
			Transform(
				Quat = Quat::Identity(),
				Vector3 = Vector3(1.0),
				Vector3 = Vector3(0.0)
			);
			Transform(const Transform& rhs);

			// Operators.
			Transform& operator = (const Transform& rhs);
			Transform operator * (const Transform& rhs) const;

			// Interface.
			Quat GetOrientation() const;
			void SetOrientation(Quat q);
			Vector3 GetScale() const;
			void SetScale(Vector3 v);
			Vector3 GetTranslation() const;
			void SetTranslation(Vector3 v);
			Matrix44 GetMatrix() const;

		private:
			// Implementation data.
			Quat mOrientation;
			Vector3 mScale;
			Vector3 mTranslation;
		};
	}
}

#include "Math/Detail/Transform.inl"
