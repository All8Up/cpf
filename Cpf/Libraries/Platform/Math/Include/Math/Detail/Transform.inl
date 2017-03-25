//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		inline Transform::Transform(Quaternionf orientation, Vector3fv scale, Vector3fv translation)
			: mOrientation(orientation)
			, mScale(scale)
			, mTranslation(translation)
		{}

		inline Transform::Transform(const Transform& rhs)
			: mOrientation(rhs.mOrientation)
			, mScale(rhs.mScale)
			, mTranslation(rhs.mTranslation)
		{}

		inline Transform& Transform::operator = (const Transform& rhs)
		{
			mOrientation = rhs.mOrientation;
			mScale = rhs.mScale;
			mTranslation = rhs.mTranslation;
			return *this;
		}

		inline Transform Transform::operator * (const Transform& rhs) const
		{
			Quaternionf q = mOrientation * rhs.mOrientation;
			Vector3fv s = mScale * rhs.mScale;
			Vector3fv t = mTranslation + mOrientation * rhs.mTranslation;

			return Transform(q, s, t);
		}

		// Interface.
		inline Quaternionf Transform::GetOrientation() const
		{
			return mOrientation;
		}

		inline void Transform::SetOrientation(Quaternionf q)
		{
			mOrientation = q;
		}

		inline Vector3fv Transform::GetScale() const
		{
			return mScale;
		}

		inline void Transform::SetScale(Vector3fv v)
		{
			mScale = v;
		}

		inline Vector3fv Transform::GetTranslation() const
		{
			return mTranslation;
		}

		inline void Transform::SetTranslation(Vector3fv v)
		{
			mTranslation = v;
		}

		inline Matrix44fv Transform::GetMatrix() const
		{
			return Matrix44fv();
		}
	}
}
