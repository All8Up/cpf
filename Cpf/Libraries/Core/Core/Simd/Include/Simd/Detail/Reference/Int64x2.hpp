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
			struct Int64x2
			{
				typedef int64_t ElementType;
				static const size_t kElementCount = 2;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(16) ValueType
				{
					ElementType data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const ElementType* const data);
				static ValueType Create(ElementType v0, ElementType v1);
				static ValueType LoadUnaligned(const ElementType* const data);
				static ElementType GetLane(ConstRef a, int idx);
				static ValueType SetLane(ConstRef a, int8_t v, int idx);

				static ValueType Add(ConstRef a, ConstRef b);
				static ValueType AddSaturate(ConstRef a, ConstRef b);
				static ValueType Sub(ConstRef a, ConstRef b);
				static ValueType SubSaturate(ConstRef a, ConstRef b);
				static ValueType And(ConstRef a, ConstRef b);
				static ValueType AndNot(ConstRef a, ConstRef b);
				static ValueType Or(ConstRef a, ConstRef b);
				static ValueType Xor(ConstRef a, ConstRef b);

				static ValueType Min(ConstRef a, ConstRef b);
				static ValueType Max(ConstRef a, ConstRef b);

				//////////////////////////////////////////////////////////////////////////
				static ValueType kZero;
				static ValueType kOne;
			};


			//////////////////////////////////////////////////////////////////////////
			inline Int64x2::ValueType Int64x2::Load(const ElementType* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Int64x2::ValueType Int64x2::Create(ElementType v0, ElementType v1)
			{
				ValueType result = { {
						v0, v1
					} };
				return result;
			}

			inline Int64x2::ValueType Int64x2::LoadUnaligned(const ElementType* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Int64x2::ElementType Int64x2::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Int64x2::ValueType Int64x2::SetLane(ConstRef a, int8_t v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Int64x2::ValueType Int64x2::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? -128 : temp;
				}
				return result;
			}

			inline Int64x2::ValueType Int64x2::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? -128 : temp;
				}
				return result;
			}

			inline Int64x2::ValueType Int64x2::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					ElementType va = ~a.data[i];
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Int64x2::ValueType Int64x2::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Int64x2::ValueType Int64x2::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
