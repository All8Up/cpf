//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		inline Transform::Transform(Quaternionfv orientation, Vector3fv scale, Vector3fv translation)
			: mOrientScale(orientation)
			, mTranslation(translation)
		{
			mOrientScale = mOrientScale * Matrix33fv::Scale(scale.x, scale.y, scale.z);
		}

		inline Transform::Transform(const Matrix33fv& orientScale, const Vector3fv& translation)
			: mOrientScale(orientScale)
			, mTranslation(translation)
		{}

		inline Transform::Transform(const Transform& rhs)
			: mOrientScale(rhs.mOrientScale)
			, mTranslation(rhs.mTranslation)
		{}

		inline Transform& Transform::operator = (const Transform& rhs)
		{
			mOrientScale = rhs.mOrientScale;
			mTranslation = rhs.mTranslation;
			return *this;
		}

		inline Transform Transform::operator * (const Transform& rhs) const
		{
			return Transform(
				mOrientScale * rhs.mOrientScale,
				mTranslation + (rhs.mTranslation * mOrientScale)
			);
		}

		// Interface.
		inline Quaternionfv Transform::GetOrientation() const
		{
			return Quaternionfv(mOrientScale);
		}

		inline void Transform::SetOrientation(Quaternionfv q)
		{
			auto scale = GetScale3(mOrientScale);
			mOrientScale = Matrix33fv(q) * Matrix33fv::Scale(scale.x, scale.y, scale.z);
		}

		inline Vector3fv Transform::GetScale() const
		{
			return GetScale3(mOrientScale);
		}

		inline void Transform::SetScale(Vector3fv v)
		{
			auto recipScale = Vector3fv(1.0f) / GetScale3(mOrientScale);
			mOrientScale = mOrientScale * Matrix33fv::Scale(recipScale);
			mOrientScale = mOrientScale * Matrix33fv::Scale(v);
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
