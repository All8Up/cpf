//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Math/Vector3v.hpp"
#include "CPF/Math/Matrix33v.hpp"
#include "CPF/Math/Matrix44v.hpp"
#include "CPF/Math/Quaternion.hpp"

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
			Transform(
				const Matrix33fv& orientScale,
				const Vector3fv& translation
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
			Matrix33fv mOrientScale;
			Vector3fv mTranslation;
		};
	}
}

#include "CPF/Math/Detail/Transform.inl"
