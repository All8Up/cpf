//////////////////////////////////////////////////////////////////////////
#include "Math/LargeVector3f.hpp"

using namespace Cpf;
using namespace Math;

/** @brief Default zeroing constructor. */
LargeVector3f::LargeVector3f()
	: mPosition(Vector3fv::Zero())
	, mHash(0)
{
}


/**
 * @brief Copy constructor.
 * @param rhs The item to copy from.
 */
LargeVector3f::LargeVector3f(const LargeVector3f& rhs)
	: mPosition(rhs.mPosition)
	, mHash(rhs.mHash)
{
}


/**
 * @brief Constructor.
 * @param pos The position.
 * @param sector The sector.
 */
LargeVector3f::LargeVector3f(const Vector3fv& pos, SpatialHashType sector)
	: mPosition(pos)
	, mHash(sector)
{
}


/**
 * @brief Assignment operator.
 * @param rhs The right hand side.
 * @return A shallow copy of this object.
 */
LargeVector3f& LargeVector3f::operator = (const LargeVector3f& rhs)
{
	mPosition = rhs.mPosition;
	mHash = rhs.mHash;
	return *this;
}


/**
 * @brief Gets local position relative to the sector origin.
 * @return The local position.
 */
Vector3fv LargeVector3f::GetLocalPosition() const
{
	return mPosition;
}


/**
 * @brief Sets the position with wrapping and/or sector updates as needed.
 * This is used for moving things around in the world and it will take care of
 * most needs.
 * @param pos The position.
 * @return eModified if the sector changed, eNone if still within the same sector.
 */
SpatialEvent LargeVector3f::SetLocalPosition(const Vector3fv& pos)
{
	// TODO: Need to check for overflow.
	// Check if this position causes wrapping into a different sector.
	Vector3fv index( (pos + Vector3fv(float(kHalfSize))) * (0.5f / kHalfSize) );
	IndexType newIndex(IndexType::VectorType(int32_t(index.x), int32_t(index.y), int32_t(index.z)));
	if (newIndex.IsZero())
	{
		mPosition = pos;
		return SpatialEvent::eNone;
	}

	// This is wrapping into a new sector.
	IndexType srcIndex = mHash.GetVector() + newIndex.GetIndex();
	mHash = srcIndex.Encode();

	// Move the position into local space of the new sector.
	mPosition = Transform(pos);
	return SpatialEvent::eModified;
}

/**
 * @brief Transforms the given position int appropriate sector coordinates.
 * @param pos The position.
 * @return The transformed position.
 */
Vector3fv LargeVector3f::Transform(const Vector3fv& pos)
{
	Vector3fv result(pos);
	result += Vector3fv(float(kHalfSize));
	result = Mod(result, Vector3fv(float(kSize))) - Vector3fv(float(kHalfSize));
	return result;
}


/**
 * @brief Gets the position relative to a given sector center.  Example usage would be
 * to get the sector of a camera and then run all objects through this to get their positions
 * appropriate for rendering.
 * @param targetSector Target sector.
 * @return The relative position.
 */
Vector3fv LargeVector3f::GetRelativePosition(SpatialHashType targetSector) const
{
	Vector3fv result = mPosition;
	if (mHash == targetSector)
		return result;

	Policy::VectorType current = mHash.GetVector();
	Policy::VectorType target = targetSector.GetVector();
	Policy::VectorType delta = target - current;

	return result - AsVector3f(delta * int32_t(kSize));
}

/**
 * @brief Gets relative position relative to the target's sector center.
 * @param targetPos Target position.
 * @return The relative position.
 */
Vector3fv LargeVector3f::GetRelativePosition(const LargeVector3f& targetPos) const
{
	return GetRelativePosition(targetPos.GetSpatialHash());
}


/**
 * @brief Gets vector to the target position.
 * @param targetPosition Target position.
 * @return The vector to the target.
 */
Vector3fv LargeVector3f::GetVectorTo(const LargeVector3f& targetPosition) const
{
	Vector3fv result = mPosition;
	if (mHash == targetPosition.GetSpatialHash())
		return result;

	Policy::VectorType current(mHash.GetVector());
	Policy::VectorType target(targetPosition.GetSpatialHash().GetVector());
	Policy::VectorType delta = target - current;

	return result - AsVector3f(delta * int32_t(kSize)) - targetPosition.GetLocalPosition();
}


/**
 * @brief Gets a unit vector towards the target position.
 * @param targetPosition Target position.
 * @return The vector towards.
 */
Vector3fv LargeVector3f::GetVectorTowards(const LargeVector3f& targetPosition) const
{
	Vector3fv result;
	// HACK: TODO: This is a cheat, there is a much more accurate solution but it is also much more involved to write.
	// This will work for most uses as long as the user re-queries (which will be most of the time).
	result = Normalize(GetVectorTo(targetPosition));
	return result;
}


/**
 * @brief Gets absolute position in full world space.  This is *very* lossy so use only for approximations.
 * @return The absolute position.
 */
Vector3fv LargeVector3f::GetAbsolutePosition() const
{
	return mPosition + AsVector3f(mHash.GetVector() * kSize);
}


/**
 * @brief Sets the position from an absolute location in world space transforming it into hash space.
 * @param pos The position.
 */
void LargeVector3f::SetAbsolutePosition(const Vector3fv& pos)
{
	// Compute the hash cell.
	Vector3fv index((pos + Vector3fv(float(kHalfSize))) * (0.5f / kHalfSize));
	IndexType newIndex(IndexType::VectorType(int32_t(index.x), int32_t(index.y), int32_t(index.z)));
	mPosition = pos;
	mHash = newIndex.Encode();

	// Move the position into local space of the hash cell.
	mPosition = Transform(pos);
}


/**
 * @brief Gets the associated Morton code.
 * @return The sector.
 */
LargeVector3f::SpatialHashType LargeVector3f::GetSpatialHash() const
{
	return mHash;
}


/**
 * @brief Sets the associated Morton code.
 * @param sector The sector.
 */
void LargeVector3f::SetSpatialHash(SpatialHashType sector)
{
	mHash = sector;
}
