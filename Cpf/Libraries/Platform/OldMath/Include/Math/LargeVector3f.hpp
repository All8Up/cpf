//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Morton.hpp"


namespace Cpf
{
	namespace Math
	{
		/** @brief Enumeration representing spatial indexing events. */
		enum class SpatialEvent : int
		{
			eNone,
			eModified,
			eInvalid
		};

		/**
		 * @brief Utility to convert 2D or 3D integral indexing into a 3D SIMD vector..
		 * @tparam TYPE Type of indexing vector.
		 * @param v The indexing vector to convert.
		 * @return v as a Vector3fv.
		 */
		template<typename TYPE>
		Vector3fv AsVector3f(const TYPE& v);

		/**
		* @brief Specialization for 2D integral indexing.  Z is zero'd.
		* @param v The index to convert.
		* @return v as a Vector3fv.
		*/
		template<> inline Vector3fv AsVector3f(const Vector2<int32_t>& v) { return Vector3fv(float(v.x), float(v.y), 0.0f); }

		/**
		* @brief Specialization for 3D integral indexing.
		* @param v The index to convert.
		* @return v as a Vector3fv.
		*/
		template<> inline Vector3fv AsVector3f(const Vector3<int32_t>& v) { return Vector3fv(float(v.x), float(v.y), float(v.z)); }

		/**
		 * @brief A Spatial indexing policy, currently based on Morton encoding.
		 * @tparam INDEXTYPE  The integral element type used within the indexing vectors (not encoded).
		 * @tparam VECTORTYPE The indexing vector type, must be integral.
		 * @tparam SPATIALTYPE The storage type for the spatial index.
		 * @tparam RESERVED   The number of bits in the spatial index type to reserve for flags.  (For instance, non-routed, transient or other flags.)
		 * @tparam DIMENSIONS The number of dimensions represented by the spatial index: 1D, 2D, 3D and potentially higher.
		 */
		template<typename INDEXTYPE, typename VECTORTYPE, typename SPATIALTYPE, const int RESERVED, const int DIMENSIONS>
		struct SpatialIndexPolicy
		{
			using IndexType = INDEXTYPE;
			using SpatialIndexType = SPATIALTYPE;
			using VectorType = VECTORTYPE;

			static const int kDimensions = DIMENSIONS;
			static const int kReservedBits = RESERVED;
			static const int kStorageBits = (sizeof(SpatialIndexType) * 8) - kReservedBits;
			static const int kElementBits = kStorageBits / kDimensions;
			static const int kMinIndex = -(1 << (kElementBits - 1));
			static const int kMaxIndex = (1 << (kElementBits - 1)) - 1;
			static const int kIndexMask = (1 << kElementBits) - 1;
			static const int kElementSize = 1 << kElementBits;
		};

		/**
		 * @brief A utility to convert to/from spatial indexing and integral vector representations.
		 * @tparam POLICY The policy for spatial indexing.
		 */
		template<typename POLICY>
		class SpatialIndex
		{
		public:
			using Policy = POLICY;
			using IndexType = typename POLICY::IndexType;
			using SpatialType = typename POLICY::SpatialIndexType;
			using VectorType = typename POLICY::VectorType;

			SpatialIndex(SpatialType v) { MortonDecode(v, mIndex); }
			SpatialIndex(const VectorType& v) : mIndex(v) {}

			bool IsZero() const { return mIndex == VectorType::Zero(); }
			SpatialType Encode() { return Morton32Encode(mIndex); }
			VectorType GetIndex() const { return mIndex; }

		private:
			VectorType mIndex;
		};

		/**
		 * @brief A container for working with the spatial hash codes.
		 * @tparam POLICY   Policy for representing the spatial hashing.
		 * @tparam HALFSIZE An integral representing the mapping of index coordinates to world coordinates.
		 */
		template<typename POLICY, const int HALFSIZE>
		class SpatialHash
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Policy = POLICY;
			using IndexType = typename Policy::IndexType;
			using HashType = typename Policy::SpatialIndexType;
			using VectorType = typename Policy::VectorType;

			//////////////////////////////////////////////////////////////////////////
			SpatialHash(HashType v) : mCode(v) {}
			SpatialHash(const SpatialHash& rhs) : mCode(rhs.mCode) {}

			bool operator ==(const SpatialHash& rhs) const { return mCode == rhs.mCode; }

			//////////////////////////////////////////////////////////////////////////
			HashType GetCode() const { return mCode; }
			VectorType GetVector() const { return SpatialIndex<Policy>(mCode).GetIndex(); }

		private:
			HashType mCode;
		};

		/** @brief A policy describing 2D Morton codes stored in 32 bits. */
		using MortonPolicy2D_32 = SpatialIndexPolicy<int32_t, Vector2<int32_t>, uint32_t, 0, 2>;
		/** @brief A policy describing 3D Morton codes stored in 32 bits. */
		using MortonPolicy3D_32 = SpatialIndexPolicy<int32_t, Vector3<int32_t>, uint32_t, 0, 3>;

		/** @brief A large world coordinate system vector3.
		 */
		class LargeVector3f
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			using Policy = MortonPolicy3D_32;
			using IndexType = SpatialIndex<Policy>;
			using SpatialHashType = SpatialHash<Policy, 8>;

			static const int kHalfSize = 8;
			static const int kSize = 2 * kHalfSize;

			//////////////////////////////////////////////////////////////////////////
			LargeVector3f();
			LargeVector3f(const LargeVector3f& rhs);
			LargeVector3f(const Vector3fv& pos, SpatialHashType sector);

			LargeVector3f& operator = (const LargeVector3f& rhs);

			//////////////////////////////////////////////////////////////////////////
			Vector3fv GetLocalPosition() const;
			SpatialEvent SetLocalPosition(const Vector3fv& pos);
			Vector3fv GetRelativePosition(SpatialHashType targetSector) const;
			Vector3fv GetRelativePosition(const LargeVector3f& targetPos) const;
			Vector3fv GetVectorTo(const LargeVector3f& targetPosition) const;
			Vector3fv GetVectorTowards(const LargeVector3f& targetPosition) const;
			Vector3fv GetAbsolutePosition() const;
			void SetAbsolutePosition(const Vector3fv& pos);

			SpatialHashType GetSpatialHash() const;
			void SetSpatialHash(SpatialHashType);

			static Vector3fv AsVector3f(const IndexType::VectorType& v) { return Math::AsVector3f(v); }

		private:
			//////////////////////////////////////////////////////////////////////////
			static Vector3fv Transform(const Vector3fv& pos);

			//////////////////////////////////////////////////////////////////////////
			Vector3fv mPosition;
			SpatialHashType mHash;
		};


		//////////////////////////////////////////////////////////////////////////
		// Validate the template computations.
		static_assert(MortonPolicy2D_32::kDimensions == 2, "Dimensions not set correctly.");
		static_assert(MortonPolicy2D_32::kStorageBits == 32, "Storage bits not calculated correctly.");
		static_assert(MortonPolicy2D_32::kElementBits == 16, "Element bits not calculated correctly.");
		static_assert(MortonPolicy2D_32::kMinIndex == -32768, "Min index not calculated correctly.");
		static_assert(MortonPolicy2D_32::kMaxIndex == 32767, "Max index not calculated correctly.");
		static_assert(MortonPolicy2D_32::kIndexMask == 0x0000FFFF, "Mask not calculated correctly.");

		//////////////////////////////////////////////////////////////////////////
		// Validate the template computations.
		static_assert(MortonPolicy3D_32::kDimensions == 3, "Dimensions not set correctly.");
		static_assert(MortonPolicy3D_32::kStorageBits == 32, "Storage bits not calculated correctly.");
		static_assert(MortonPolicy3D_32::kElementBits == 10, "Element bits not calculated correctly.");
		static_assert(MortonPolicy3D_32::kMinIndex == -512, "Min index not calculated correctly.");
		static_assert(MortonPolicy3D_32::kMaxIndex == 511, "Max index not calculated correctly.");
		static_assert(MortonPolicy3D_32::kIndexMask == 0x03FF, "Mask not calculated correctly.");
	}
}
