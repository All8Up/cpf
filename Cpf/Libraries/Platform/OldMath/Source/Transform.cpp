//////////////////////////////////////////////////////////////////////////
#include "Math/Transform.hpp"
#include "Math/Matrix33v.hpp"
#include "Math/Matrix44v.hpp"

using namespace Cpf;
using namespace Math;

/** @brief Default constructor. */
Transform::Transform(Quaternionfv q, Vector3fv s, Vector3fv t)
	: mOrientation(q)
	, mScale(s)
	, mTranslation(t)
{}

/**
 @brief Copy constructor.
 @param rhs The right hand side.
 */
Transform::Transform(const Transform& rhs)
	: mOrientation(rhs.mOrientation)
	, mScale(rhs.mScale)
	, mTranslation(rhs.mTranslation)
{}

/**
 @brief Assignment operator.
 @param rhs The right hand side.
 */
Transform& Transform::operator = (const Transform& rhs)
{
	mOrientation = rhs.mOrientation;
	mScale = rhs.mScale;
	mTranslation = rhs.mTranslation;
	return *this;
}

Transform Transform::operator * (const Transform& rhs) const
{
	return Transform(
		mOrientation * rhs.mOrientation,
		mScale * rhs.mScale,
		mTranslation + mOrientation * rhs.mTranslation
	);
}

/**
 @brief Gets the orientation.
 @return The orientation.
 */
Quaternionfv Transform::GetOrientation() const
{
	return mOrientation;
}

/**
 @brief Sets the orientation.
 @param q The quaternion value.
 */
void Transform::SetOrientation(Quaternionfv q)
{
	mOrientation = q;
}

/**
 @brief Gets the scale.
 @return The scale.
 */
Vector3fv Transform::GetScale() const
{
	return mScale;
}

/**
 @brief Sets a scale.
 @param v The vector value.
 */
void Transform::SetScale(Vector3fv v)
{
	mScale = v;
}

/**
 @brief Gets the translation.
 @return The translation.
 */
Vector3fv Transform::GetTranslation() const
{
	return mTranslation;
}

/**
 @brief Sets a translation.
 @param v The vector value.
 */
void Transform::SetTranslation(Vector3fv v)
{
	mTranslation = v;
}

/**
 @brief Get the transform as a matrix.
 @return The resulting matrix 4x4.
 */
Matrix44fv Transform::GetMatrix() const
{
	Matrix33fv orientation(mOrientation);
	Matrix44fv result(
		Vector4fv(orientation[0].xyz, 0.0f) * mScale.x,
		Vector4fv(orientation[1].xyz, 0.0f) * mScale.y,
		Vector4fv(orientation[2].xyz, 0.0f) * mScale.z,
		Vector4fv(mTranslation, 1.0f)
	);
	return result;
}
