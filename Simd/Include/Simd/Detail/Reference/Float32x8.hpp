//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Configuration/Configuration.hpp>

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Reference
		{
			/**
			*/
			struct Float32x8
			{
				using ElementType = float;
				static const size_t kElementCount = 8;

				struct CPF_ALIGN(32) ValueType
				{
					float data[kElementCount];
				};
				using ConstRef = ValueType const&;

				static ValueType Load(const float* const data);
				static ValueType Create(float v0, float v1, float v2, float v3, float v4, float v5, float v6, float v7);
				static ValueType LoadUnaligned(const float* const data);
				static float GetLane(ConstRef a, int idx);
				static ValueType SetLane(float v, ConstRef a, int idx);

				static ValueType Add(ConstRef a, ConstRef b);
				static ValueType Sub(ConstRef a, ConstRef b);
				static ValueType Mul(ConstRef a, ConstRef b);
				static ValueType Div(ConstRef a, ConstRef b);

				static ValueType Min(ConstRef a, ConstRef b);
				static ValueType Max(ConstRef a, ConstRef b);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Float32x8::ValueType Float32x8::Load(const float* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Create(float v0, float v1, float v2, float v3, float v4, float v5, float v6, float v7)
			{
				ValueType result = { { v0, v1, v2, v3, v4, v5, v6, v7 } };
				return result;
			}

			inline Float32x8::ValueType Float32x8::LoadUnaligned(const float* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline float Float32x8::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Float32x8::ValueType Float32x8::SetLane(float v, ConstRef a, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Float32x8::ValueType Float32x8::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Mul(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] * b.data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Div(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] / b.data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] < b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Float32x8::ValueType Float32x8::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] > b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
