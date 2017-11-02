//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		inline Transform::Transform(Quat orientation, Vector3 scale, Vector3 translation)
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
			Quat q = mOrientation * rhs.mOrientation;
			Vector3 s = mScale * rhs.mScale;
			Vector3 t = mTranslation + mOrientation * rhs.mTranslation;

			return Transform(q, s, t);
		}

		// Interface.
		inline Transform::Quat Transform::GetOrientation() const
		{
			return mOrientation;
		}

		inline void Transform::SetOrientation(Quat q)
		{
			mOrientation = q;
		}

		inline Transform::Vector3 Transform::GetScale() const
		{
			return mScale;
		}

		inline void Transform::SetScale(Vector3 v)
		{
			mScale = v;
		}

		inline Transform::Vector3 Transform::GetTranslation() const
		{
			return mTranslation;
		}

		inline void Transform::SetTranslation(Vector3 v)
		{
			mTranslation = v;
		}

		inline Transform::Matrix44 Transform::GetMatrix() const
		{
			return Matrix44();
		}
	}
}
