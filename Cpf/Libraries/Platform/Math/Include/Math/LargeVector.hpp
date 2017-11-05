//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Vector3v.hpp"

namespace CPF
{
	namespace Math
	{
		/**
		 * @class Proxy
		 * @brief A proxy is a simple, though ugly and potentially unsafe
		 * if used incorrectly, reference to the containing object.  The
		 * purpose of this is to implement properties much like C# which
		 * are accessed via simple member value (i.e. 'a.b' style) syntax
		 * yet will go through get/set like operations.  This is needed
		 * in cases where the property can not safely have it's address
		 * taken or it doesn't exist in the form being represented.
		 * In all current compilers this has been tested and will be
		 * optimized away such that there is no additional overhead to
		 * using the proxy.
		 * @tparam VALUETYPE The value type that is represented by the proxy.
		 */
		template <typename TYPE>
		class Proxy
		{
		public:
			using ValueType = TYPE;

		protected:
			TYPE* Get()
			{
				union Converter
				{
					Converter(uint8_t* source) : mpSource(source) {}
					uint8_t* mpSource;
					ValueType* mpTarget;
				} convert(mSource);
				return convert.mpTarget;
			}
			const TYPE* Get() const
			{
				union Converter
				{
					Converter(const uint8_t* source) : mpSource(source) {}
					const uint8_t* mpSource;
					const ValueType* mpTarget;
				} convert(mSource);
				return convert.mpTarget;
			}

		private:
			uint8_t mSource[1];
		};

		template <typename DESC>
		struct CoordinateLaneRef : Proxy<CoordinateLaneRef<DESC>>
		{
		};

		template <typename DESC, typename TYPE>
		struct CoordinateRef : Proxy<CoordinateRef<DESC, TYPE>>
		{
			CoordinateRef<DESC, TYPE>& operator = (TYPE value)
			{
				return *this;
			}
		};

		/**
		 * @struct WorldSpaceProxy
		 * @brief A proxy of large coordinates which manipulates the coordinates in world space.
		 * @tparam DESC The descriptor which is applied to large coordinates.
		 */
		template <typename DESC>
		struct WorldSpaceProxy : Proxy<WorldSpaceProxy<DESC>>
		{
			CoordinateRef<DESC, typename DESC::WorldType> vector;
			CoordinateLaneRef<DESC> x;
			CoordinateLaneRef<DESC> y;
			CoordinateLaneRef<DESC> z;
		};

		template <typename DESC>
		union LargeVector
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

			WorldSpaceProxy<DESC> world;

		private:
			StorageType mStorage;
		};

		//////////////////////////////////////////////////////////////////////////
		template <typename STORAGETYPE, typename REPTYPE, int DIMENSIONS, int BITS>
		union Sector;

		//////////////////////////////////////////////////////////////////////////
		// int32_t 3D sector.
		template <>
		union Sector<int32_t, Vector3<SIMD::I32x4_3>, 3, 10>
		{
			using StorageType = int32_t;
			using SectorRep = Vector3<SIMD::I32x4_3>;
			using LaneType = Vector3<SIMD::I32x4_3>::LaneType;
			static constexpr int32_t Dimensions = 3;
			static constexpr int32_t Bits = 10;

			explicit Sector(StorageType value) : mSector(value) {}
			Sector(LaneType x, LaneType y, LaneType z) : mSector(0) { mElements.x = x; mElements.y = y; mElements.z = z; }
			explicit Sector(SectorRep v) { mElements.x = v.x; mElements.y = v.y; mElements.z = v.z; }

			explicit operator StorageType () const { return mSector; }
			explicit operator SectorRep() const { return SectorRep(mElements.x, mElements.y, mElements.z); }

			int32_t GetX() const { return mElements.x; }
			void SetX(int32_t x) { mElements.x = x; }
			int32_t GetY() const { return mElements.y; }
			void SetY(int32_t y) { mElements.y = y; }
			int32_t GetZ() const { return mElements.z; }
			void SetZ(int32_t z) { mElements.z = z; }

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
			using SectorRep = Vector3<SIMD::I32x4_3>;
			using SectorType = Sector<int32_t, SectorRep, 3, 10>;
			using StorageType = SIMD::F32x4;
			using RelativeType = float;
			using WorldType = double;
		};
	}
}


#include "Detail/LargeVector.inl"
