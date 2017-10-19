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

			using PositionType = typename DESC::PositionType;
			using SectorType = typename DESC::SectorType;
			using StorageType = typename DESC::StorageType;
			using SectorRep = typename DESC::SectorRep;

			static constexpr int HalfBound = DESC::HalfBound;

			LargeVector() {}
			LargeVector(const LargeVector& rhs) : mStorage(rhs.mStorage) {}
			LargeVector(LargeVector&& rhs) noexcept : mStorage(rhs.mStorage) {}
			explicit LargeVector(const StorageType& rhs) : mStorage(rhs) {}

			LargeVector& operator =(const LargeVector& rhs) { mStorage = rhs.mStorage; return *this; }
			LargeVector& operator =(LargeVector&& rhs) noexcept { mStorage = rhs.mStorage; return *this; }

			operator StorageType() const { return mStorage; }

		private:
			StorageType mStorage;
		};

		//////////////////////////////////////////////////////////////////////////
		// SIMD floating point representation.
		struct LargeVectorFI
		{
			static constexpr int HalfBound = 5;

			using PositionType = Vector3fv;
			using SectorType = int32_t;
			using SectorRep = Vector3v<SIMD::I32x4>;
			using StorageType = SIMD::F32x4;
		};
	}
}
