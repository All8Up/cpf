//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/SIMD/Rounding.hpp"
#include "CPF/SIMD/Detail/SSE4_1/Bool4.hpp"
#include <emmintrin.h>
#include <smmintrin.h>

namespace CPF
{
	namespace SIMD
	{
		namespace SSE4_1
		{
			struct alignas(16) double4
			{
				__m128d mData[2];
			};

			//////////////////////////////////////////////////////////////////////////
			template <typename STORAGE_TYPE, typename LANE_TYPE, int LANES_USED>
			struct alignas(16) F64x4;

			/**
			 * @struct F64x4
			 * @brief Specialization of F64x4 which is implemented on top of two __m128 registers.
			 * @tparam LANES_USED Number of lanes in use within the simd type.
			 */
			template<int LANES_USED>
			struct alignas(16) F64x4<double4, double, LANES_USED>
			{
				// Implementation details.
				using StorageType = double4;
				using LaneType = double;
				using BoolType = Bool4<__m128i, bool, LANES_USED>;
				static constexpr int LaneCount = LANES_USED;
				static constexpr int LaneMask = (1 << LaneCount) - 1;

				using Lanes_1 = F64x4<double4, double, 1>;
				using Lanes_2 = F64x4<double4, double, 2>;
				using Lanes_3 = F64x4<double4, double, 3>;
				using Lanes_4 = F64x4<double4, double, 4>;

				// Default construction.
				F64x4();
				F64x4(StorageType value) : mSIMD(value) {}

				// Construct from 1, 2, 3 or 4 element initializers.
				explicit F64x4(LaneType value);

				F64x4(LaneType v0, LaneType v1);
				F64x4(LaneType v0, LaneType v1, LaneType v2);
				F64x4(LaneType v0, LaneType v1, LaneType v2, LaneType v3);

				// Construct from 1, 2 lane and 1 element initializer.
				F64x4(Lanes_2 v01, LaneType v2);
				F64x4(LaneType v0, Lanes_2 v12);

				// Construction from 1, 2 lane and 2 element initializers.
				F64x4(Lanes_2 v01, LaneType v2, LaneType v3);
				F64x4(LaneType v0, Lanes_2 v12, LaneType v3);
				F64x4(LaneType v0, LaneType v1, Lanes_2 v23);

				// Construct from 2, 2 lane initializers.
				F64x4(Lanes_2 v01, Lanes_2 v23);

				// Construct from 1, 3 lane and 1 element initializer.
				F64x4(Lanes_3 v012, LaneType v3);
				F64x4(LaneType v0, Lanes_3 v123);

				// Assign from raw simd type.
				F64x4& operator = (StorageType value);

				// Explicit conversion to raw simd type.
				explicit operator StorageType () const;

				// Implicit conversion of lane 0 to a raw element type, unwrapping the data to non-simd.
				operator const LaneType() const;

				// Lane accessors.
				void SetLane(int index, double value);
				template <int I0> LaneType GetLane() const;
				template <int I0, int I1> Lanes_2 GetLanes() const;
				template <int I0, int I1, int I2> Lanes_3 GetLanes() const;
				template <int I0, int I1, int I2, int I3> Lanes_4 GetLanes() const;

				// Raw simd type.
				StorageType mSIMD;
			};

			//////////////////////////////////////////////////////////////////////////
			using F64x4_1 = F64x4<double4, double, 1>;
			using F64x4_2 = F64x4<double4, double, 2>;
			using F64x4_3 = F64x4<double4, double, 3>;
			using F64x4_4 = F64x4<double4, double, 4>;

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			using F64x4_ = F64x4<double4, double, COUNT>;
		}
	}
}

#include "F64x4_access.inl"
#include "F64x4_construction.inl"
#include "F64x4_comparison.inl"
#include "F64x4_operations.inl"
