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
				Quaternionfv = Quaternionfv::Identity(),
				Vector3fv = Vector3fv(1.0),
				Vector3fv = Vector3fv(0.0)
			);
			Transform(const Transform& rhs);

			// Operators.
			Transform& operator = (const Transform& rhs);
			Transform operator * (const Transform& rhs) const;

			// Interface.
			Quaternionfv GetOrientation() const;
			void SetOrientation(Quaternionfv q);
			Vector3fv GetScale() const;
			void SetScale(Vector3fv v);
			Vector3fv GetTranslation() const;
			void SetTranslation(Vector3fv v);
			Matrix44fv GetMatrix() const;

		private:
			// Implementation data.
			Quaternionfv mOrientation;
			Vector3fv mScale;
			Vector3fv mTranslation;
		};
	}
}

#include "Math/Detail/Transform.inl"
