//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename DESC>
		struct LargeVector
		{
			using Description = DESC;

			using VectorType = typename DESC::VectorType;
			using SectorType = typename DESC::SectorType;
			using SectorRep = typename DESC::SectorType::SectorRep;
			using StorageType = typename DESC::StorageType;

			static constexpr int HalfBound = DESC::HalfBound;

			LargeVector() {}
			LargeVector(const LargeVector& rhs) : mStorage(rhs.mStorage) {}
			LargeVector(LargeVector&& rhs) noexcept : mStorage(rhs.mStorage) {}
			explicit LargeVector(const StorageType& rhs) : mStorage(rhs) {}
			explicit LargeVector(const VectorType& vt, const SectorType& st) : mStorage(vt.xyz, *reinterpret_cast<const float*>(&st)) {}

			LargeVector& operator =(const LargeVector& rhs) { mStorage = rhs.mStorage; return *this; }
			LargeVector& operator =(LargeVector&& rhs) noexcept { mStorage = rhs.mStorage; return *this; }

			operator StorageType() const { return mStorage; }

		private:
			StorageType mStorage;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename STORAGETYPE, typename REPTYPE, int DIMENSIONS, int BITS>
		union Sector;

		//////////////////////////////////////////////////////////////////////////
		// int32_t 3D sector.
		template <>
		union Sector<int32_t, Vector3v<SIMD::I32x4_3>, 3, 10>
		{
			using StorageType = int32_t;
			using SectorRep = Vector3v<SIMD::I32x4_3>;
			using LaneType = Vector3v<SIMD::I32x4_3>::LaneType;
			static constexpr int32_t Dimensions = 3;
			static constexpr int32_t Bits = 10;

			explicit Sector(StorageType value) : mSector(value) {}
			Sector(LaneType x, LaneType y, LaneType z) : mSector(0) { mElements.x = x; mElements.y = y; mElements.z = z; }
			explicit operator StorageType () const { return mSector; }

			int32_t GetX() const { return mElements.x; }
			void SetX(int32_t x) { mElements.x = x; }
			int32_t GetY() const { return mElements.y; }
			void SetY(int32_t y) { mElements.y = y; }
			int32_t GetZ() const { return mElements.z; }
			void SetZ(int32_t z) { mElements.z = z; }

			Vector3v<SIMD::I32x4_3> AsRep() const { return Vector3v<SIMD::I32x4_3>(mElements.x, mElements.y, mElements.z); }
			void FromRep(Vector3v<SIMD::I32x4_3> v) { mElements.x = v.x; mElements.y = v.y; mElements.z = v.z; }

		private:
			struct
			{
				int32_t x : Bits;
				int32_t y : Bits;
				int32_t z : Bits;
			} mElements;
			StorageType mSector;
		};

		template <typename STORAGETYPE, typename REPTYPE, int DIMENSIONS, int BITS>
		bool operator == (Sector<STORAGETYPE, REPTYPE, DIMENSIONS, BITS> lhs, Sector<STORAGETYPE, REPTYPE, DIMENSIONS, BITS> rhs)
		{
			using StorageType = typename Sector<STORAGETYPE, REPTYPE, DIMENSIONS, BITS>::StorageType;
			return StorageType(lhs) == StorageType(rhs);
		}

		//////////////////////////////////////////////////////////////////////////
		// SIMD floating point representation.
		struct LargeVectorDesc_FI
		{
			static constexpr int HalfBound = 5;

			using VectorType = Vector3fv;
			using SectorRep = Vector3v<SIMD::I32x4_3>;
			using SectorType = Sector<int32_t, SectorRep, 3, 10>;
			using StorageType = SIMD::F32x4;
		};
	}
}


#include "Detail/LargeVector.inl"
