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
			struct Float64x2
			{
				typedef float ElementType;
				static const size_t kElementCount = 2;

				struct CPF_ALIGN(16) ValueType
				{
					double data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				static ValueType Load(const double* const data);
				static ValueType Create(double v0, double v1);
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
			inline Float64x2::ValueType Float64x2::Load(const double* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Create(double v0, double v1)
			{
				ValueType result = { {v0, v1} };
				return result;
			}

			inline Float64x2::ValueType Float64x2::LoadUnaligned(const double* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline double Float64x2::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Float64x2::ValueType Float64x2::SetLane(double v, ConstRef a, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Float64x2::ValueType Float64x2::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Mul(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] * b.data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Div(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] / b.data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] < b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Float64x2::ValueType Float64x2::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] > b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
