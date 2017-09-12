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
			// Construction.
			Transform(
				Quaternionf = Quaternionf::Identity(),
				Vector3fv = Vector3fv(1.0f),
				Vector3fv = Vector3fv(0.0f)
			);
			Transform(const Transform& rhs);

			// Operators.
			Transform& operator = (const Transform& rhs);
			Transform operator * (const Transform& rhs) const;

			// Interface.
			Quaternionf GetOrientation() const;
			void SetOrientation(Quaternionf q);
			Vector3fv GetScale() const;
			void SetScale(Vector3fv v);
			Vector3fv GetTranslation() const;
			void SetTranslation(Vector3fv v);
			Matrix44fv GetMatrix() const;

		private:
			// Implementation data.
			Quaternionf mOrientation;
			Vector3fv mScale;
			Vector3fv mTranslation;
		};
	}
}

#include "Math/Detail/Transform.inl"
