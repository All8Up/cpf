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
#define DOUBLE_TRANSFORM 0
#if DOUBLE_TRANSFORM
			using Real = double;
			using Quaternion = Quaterniond;
			using Vector3 = Vector3dv;
			using Matrix44 = Matrix44dv;
#else
			using Real = float;
			using Quaternion = Quaternionf;
			using Vector3 = Vector3fv;
			using Matrix44 = Matrix44fv;
#endif

			// Construction.
			Transform(
				Quaternion = Quaternion::Identity(),
				Vector3 = Vector3(1.0),
				Vector3 = Vector3(0.0)
			);
			Transform(const Transform& rhs);

			// Operators.
			Transform& operator = (const Transform& rhs);
			Transform operator * (const Transform& rhs) const;

			// Interface.
			Quaternion GetOrientation() const;
			void SetOrientation(Quaternion q);
			Vector3 GetScale() const;
			void SetScale(Vector3 v);
			Vector3 GetTranslation() const;
			void SetTranslation(Vector3 v);
			Matrix44 GetMatrix() const;

		private:
			// Implementation data.
			Quaternion mOrientation;
			Vector3 mScale;
			Vector3 mTranslation;
		};
	}
}

#include "Math/Detail/Transform.inl"
