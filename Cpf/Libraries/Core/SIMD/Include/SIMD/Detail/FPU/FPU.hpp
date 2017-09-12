//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include <cmath>

namespace CPF
{
	namespace SIMD
	{
		namespace FPU
		{
			CPF_FORCE_INLINE bool Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
			}

			struct float1
			{
				float1() {}
				float1(float v0) : mData{ v0 } {}

				float mData[1];
			};

			struct float2
			{
				float2() {}
				float2(float v0) : mData{ v0, v0 } {}
				float2(float v0, float v1) : mData{ v0, v1 } {}

				float mData[2];
			};

			struct float3
			{
				float3() {}
				float3(const float3& rhs) : mData{ rhs.mData[0], rhs.mData[1], rhs.mData[2] } {}
				float3(float v0) : mData{ v0, v0, v0 } {}
				float3(float v0, float v1) : mData{ v0, v1, v0 } {}
				float3(float v0, float v1, float v2) : mData{ v0, v1, v2 } {}

				float mData[3];
			};

			struct float4
			{
				float4() {}
				float4(float v0) : mData{ v0, v0, v0, v0 } {}
				float4(float v0, float v1) : mData{ v0, v1, v0, v0 } {}
				float4(float v0, float v1, float v2) : mData{ v0, v1, v2, v0 } {}
				float4(float v0, float v1, float v2, float v3) : mData{ v0, v1, v2, v3 } {}

				float mData[4];
			};

			//////////////////////////////////////////////////////////////////////////
			struct int1
			{
				int1() {}
				int1(int32_t v0) : mData{ v0 } {}

				int32_t mData[1];
			};

			struct int2
			{
				int2() {}
				int2(int32_t v0) : mData{ v0, v0 } {}
				int2(int32_t v0, int32_t v1) : mData{ v0, v1 } {}

				int32_t mData[2];
			};

			struct int3
			{
				int3() {}
				int3(int32_t v0) : mData{ v0, v0, v0 } {}
				int3(int32_t v0, int32_t v1) : mData{ v0, v1, v0 } {}
				int3(int32_t v0, int32_t v1, int32_t v2) : mData{ v0, v1, v2 } {}

				int32_t mData[3];
			};

			struct int4
			{
				int4() {}
				int4(int32_t v0) : mData{ v0, v0, v0, v0 } {}
				int4(int32_t v0, int32_t v1) : mData{ v0, v1, v0, v0 } {}
				int4(int32_t v0, int32_t v1, int32_t v2) : mData{ v0, v1, v2, v0 } {}
				int4(int32_t v0, int32_t v1, int32_t v2, int32_t v3) : mData{ v0, v1, v2, v3 } {}

				int32_t mData[4];
			};

			//////////////////////////////////////////////////////////////////////////
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) F32x1;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) F32x2;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) F32x3;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) F32x4;

			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) I32x1;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) I32x2;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) I32x3;
			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) I32x4;

			template <typename TYPE, typename LANE_TYPE, int COUNT>
			struct alignas(4) Bool4;
		}
	}
}
