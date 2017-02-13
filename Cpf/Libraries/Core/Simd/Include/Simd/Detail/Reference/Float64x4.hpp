//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Reference
		{
			/**
			*/
			struct Float64x4
			{
				typedef float ElementType;
				static const size_t kElementCount = 4;

				struct CPF_ALIGN(16) ValueType
				{
					double data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				static ValueType Load(const double* const data);
				static ValueType Create(double v0, double v1, double v2, double v3);
				static ValueType LoadUnaligned(const double* const data);
				static double GetLane(ConstRef a, int idx);
				static ValueType SetLane(double v, ConstRef a, int idx);

				static ValueType Add(ConstRef a, ConstRef b);
				static ValueType Sub(ConstRef a, ConstRef b);
				static ValueType Mul(ConstRef a, ConstRef b);
				static ValueType Div(ConstRef a, ConstRef b);

				static ValueType Min(ConstRef a, ConstRef b);
				static ValueType Max(ConstRef a, ConstRef b);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Float64x4::ValueType Float64x4::Load(const double* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Create(double v0, double v1, double v2, double v3)
			{
				ValueType result = { { v0, v1, v2, v3 } };
				return result;
			}

			inline Float64x4::ValueType Float64x4::LoadUnaligned(const double* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline double Float64x4::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Float64x4::ValueType Float64x4::SetLane(double v, ConstRef a, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Float64x4::ValueType Float64x4::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Mul(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] * b.data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Div(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] / b.data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] < b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Float64x4::ValueType Float64x4::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] > b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
