//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Quaternionv.hpp"

namespace Cpf
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
				Vector3fv = Vector3fv(1.0f),
				Vector3fv = Vector3fv::Zero()
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
