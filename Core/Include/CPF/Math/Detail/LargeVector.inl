//////////////////////////////////////////////////////////////////////////
#pragma once

namespace CPF
{
	namespace Math
	{
		template <>
		LargeVector3fv_t& Set(LargeVector3fv_t& largeVector,
			const Vector3fv v,
			const Vector3iv s)
		{
			SectorCodecI32x3 encode(s);
			largeVector.mData = Vector4fv(v.xyz, encode.mStorage);
			return largeVector;
		}

		template <>
		Vector3iv GetSector(const LargeVector3fv_t lg)
		{
			SectorCodecI32x3 decode(lg.mData.w);
			return Vector3iv(decode.mFields.mX, decode.mFields.mY, decode.mFields.mZ);
		}

		template <>
		LargeVector3fv_t& SetSector(LargeVector3fv_t& largeVector, const Vector3iv s)
		{
			SectorCodecI32x3 encode(s);
			largeVector.mData = LargeVector3fv_t::StorageType(largeVector.mData.xyz, encode.mStorage);
			return largeVector;
		}

		template <>
		LargeVector3fv_t::VectorType GetVector(const LargeVector3fv_t largeVector)
		{
			return LargeVector3fv_t::VectorType(largeVector.mData.xyz);
		}
		template <>
		LargeVector3fv_t& SetVector(LargeVector3fv_t& largeVector, const LargeVector3fv_t::VectorType v)
		{
			largeVector.mData = LargeVector3fv_t::StorageType(v.xyz, largeVector.mData.w);
			return largeVector;
		}

		template <>
		LargeVector3fv_t GetSectorized(const LargeVector3fv_t& lv)
		{
			// TODO: Check the disassembly, probably need a way to make static constexpr
			// versions of simd types.
			static Vector3fv sectorHalfSize(kHalfSectorSize);
			static Vector3fv sectorSize(kSectorSize);
			static Vector3fv ooSectorSize(1.0f / kSectorSize);
			static Vector3fv zero(0.0f);

			Vector3fv v = GetVector(lv);
			Vector3iv s = GetSector(lv);

			Vector3fv unitized = (v + sectorHalfSize) * ooSectorSize;
			// TODO: Check for, and add if missing, single instruction float->int simd specialization.
			Vector3iv sectorOffset = Vector3iv(unitized);
			Vector3iv predValue(unitized < zero);

			Vector3fv vOffset = Vector3fv(sectorOffset + predValue) * sectorSize;

			LargeVector3fv_t result;
			Vector3fv newVector = v - vOffset;
			Vector3iv newSector = s + (sectorOffset + predValue);
			Set(result, newVector, newSector);

			return LargeVector3fv_t(result);
		}

		template <>
		LargeVector3fv_t operator +(const LargeVector3fv_t& lhs, const Vector3fv& rhs)
		{
			LargeVector3fv_t result;
			return GetSectorized(Set(result, GetVector(lhs) + rhs, GetSector(lhs)));
		}

		template <>
		LargeVector3fv_t operator +(const LargeVector3fv_t& lhs, const LargeVector3fv_t& rhs)
		{
			LargeVector3fv_t result;
			return GetSectorized(Set(result, GetVector(lhs) + GetVector(rhs), GetSector(rhs) - GetSector(lhs)));
		}

		template <>
		LargeVector3fv_t operator -(const LargeVector3fv_t& lhs, const Vector3fv& rhs)
		{
			LargeVector3fv_t result;
			return GetSectorized(Set(result, GetVector(lhs) - rhs, GetSector(lhs)));
		}

		template <>
		LargeVector3fv_t operator -(const LargeVector3fv_t& lhs, const LargeVector3fv_t& rhs)
		{
			LargeVector3fv_t result;
			return GetSectorized(Set(result, GetVector(lhs) - GetVector(rhs), GetSector(rhs) - GetSector(lhs)));
		}
	}
}
