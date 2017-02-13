//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Configuration/Configuration.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Reference
		{
			/**
			*/
			struct Float32x4
			{
				using ElementType = float;
				static const size_t kElementCount = 4;

				struct CPF_ALIGN(16) ValueType
				{
					float data[kElementCount];
				};
				using ConstRef = ValueType const&;

				//////////////////////////////////////////////////////////////////////////
				static const ValueType kZero;
				static const ValueType kOne;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const float* const data);
				static ValueType Create(float v0, float v1, float v2, float v3);
				static ValueType LoadUnaligned(const float* const data);
				static float GetLane(ConstRef a, int idx);
				static ValueType SetLane(float v, ConstRef a, int idx);

				static ValueType Splat(ConstRef value, int idx);

				static bool IsValid(ConstRef a);
				static bool Equal(ConstRef a, ConstRef b);

				static ValueType Negate3(ConstRef a);
				static ValueType Negate4(ConstRef a);

				static ValueType Add3(ConstRef a, ConstRef b);
				static ValueType Add4(ConstRef a, ConstRef b);

				static ValueType Sub3(ConstRef a, ConstRef b);
				static ValueType Sub4(ConstRef a, ConstRef b);

				static ValueType Mul4(ConstRef a, ConstRef b);
				static ValueType Div4(ConstRef a, ConstRef b);

				static ValueType Min4(ConstRef a, ConstRef b);
				static ValueType Max4(ConstRef a, ConstRef b);

				static float Dot3(ConstRef a, ConstRef b);
				static float Dot4(ConstRef a, ConstRef b);
				static float Mag3(ConstRef a);
				static ValueType Norm3(ConstRef a);
				static ValueType Norm4(ConstRef a);

				static ValueType Cross3(ConstRef a, ConstRef b);

				static ValueType SpliceLow(ConstRef a, ConstRef b);
				static ValueType SpliceHigh(ConstRef a, ConstRef b);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Float32x4::ValueType Float32x4::Load(const float* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Create(float v0, float v1, float v2, float v3)
			{
				ValueType result = { {v0, v1, v2, v3} };
				return result;
			}

			inline Float32x4::ValueType Float32x4::LoadUnaligned(const float* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline float Float32x4::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Float32x4::ValueType Float32x4::SetLane(float v, ConstRef a, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Float32x4::ValueType Float32x4::Splat(ConstRef value, int idx)
			{
				return Float32x4::Create(value.data[idx], value.data[idx], value.data[idx], value.data[idx]);
			}

			inline bool Float32x4::IsValid(ConstRef a)
			{
				ValueType test = Mul4(a, kZero);
				for (int i = 0; i < kElementCount; ++i)
					if (test.data[i] != 0.0f)
						return false;
				return true;
			}

			inline bool Float32x4::Equal(ConstRef a, ConstRef b)
			{
				for (int i = 0; i < kElementCount; ++i)
					if (a.data[i] != b.data[i])
						return false;
				return true;
			}

			inline Float32x4::ValueType Float32x4::Negate3(ConstRef a)
			{
				ValueType result = { {-a.data[0], -a.data[1], -a.data[2], a.data[3]} };
				return result;
			}

			inline Float32x4::ValueType Float32x4::Negate4(ConstRef a)
			{
				ValueType result = { {-a.data[0], -a.data[1], -a.data[2], -a.data[3]} };
				return result;
			}

			inline Float32x4::ValueType Float32x4::Add3(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < 3; ++i)
					result.data[i] = a.data[i] + b.data[i];
				result.data[3] = a.data[3];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Add4(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Sub3(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < 3; ++i)
					result.data[i] = a.data[i] - b.data[i];
				result.data[3] = a.data[3];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Sub4(ConstRef a, ConstRef b)
			{
				ValueType result = { 0 };
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Mul4(ConstRef a, ConstRef b)
			{
				ValueType result = { 0 };
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] * b.data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Div4(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] / b.data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Min4(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] < b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Float32x4::ValueType Float32x4::Max4(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] > b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline float Float32x4::Dot3(ConstRef a, ConstRef b)
			{
				return
					(a.data[0] * b.data[0]) +
					(a.data[1] * b.data[1]) +
					(a.data[2] * b.data[2]);
			}

			inline float Float32x4::Dot4(ConstRef a, ConstRef b)
			{
				return
					(a.data[0] * b.data[0]) +
					(a.data[1] * b.data[1]) +
					(a.data[2] * b.data[2]) +
					(a.data[3] * b.data[3]);
			}

			inline float Float32x4::Mag3(ConstRef a)
			{
				return std::sqrt(
					(a.data[0] * a.data[0]) +
					(a.data[1] * a.data[1]) +
					(a.data[2] * a.data[2]));
			}

			inline Float32x4::ValueType Float32x4::Norm3(ConstRef a)
			{
				float mag = 1.0f / std::sqrt(
					(a.data[0] * a.data[0]) +
					(a.data[1] * a.data[1]) +
					(a.data[2] * a.data[2]));

				ValueType result = a;
				result.data[0] *= mag;
				result.data[1] *= mag;
				result.data[2] *= mag;

				return result;
			}

			inline Float32x4::ValueType Float32x4::Norm4(ConstRef a)
			{
				float mag = 1.0f / std::sqrt(
					(a.data[0] * a.data[0]) +
					(a.data[1] * a.data[1]) +
					(a.data[2] * a.data[2]) +
					(a.data[3] * a.data[3]));

				ValueType result = a;
				result.data[0] *= mag;
				result.data[1] *= mag;
				result.data[2] *= mag;
				result.data[3] *= mag;

				return result;
			}

			inline Float32x4::ValueType Float32x4::Cross3(ConstRef a, ConstRef b)
			{
				ValueType result =
				{ {
					(a.data[1] * b.data[2] - a.data[2] * b.data[1]),
					(a.data[2] * b.data[0] - a.data[0] * b.data[2]),
					(a.data[0] * b.data[1] - a.data[1] * b.data[0]),
					0.0f
				} };
				return result;
			}

			inline Float32x4::ValueType Float32x4::SpliceLow(ConstRef a, ConstRef b)
			{
				ValueType result =
				{ {
					a.data[0],
					b.data[0],
					a.data[1],
					b.data[1]
				} };
				return result;
			}

			inline Float32x4::ValueType Float32x4::SpliceHigh(ConstRef a, ConstRef b)
			{
				ValueType result =
				{ {
					a.data[2],
					b.data[2],
					a.data[3],
					b.data[3]
				} };
				return result;
			}
		}
	}
}
