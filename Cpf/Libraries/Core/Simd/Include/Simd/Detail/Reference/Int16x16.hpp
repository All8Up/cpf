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
			struct Int16x16
			{
				typedef int16_t ElementType;
				static const size_t kElementCount = 16;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(32) ValueType
				{
					ElementType data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const ElementType* const data);
				static ValueType Create(
					ElementType v0, ElementType v1, ElementType v2, ElementType v3, ElementType v4, ElementType v5, ElementType v6, ElementType v7,
					ElementType v8, ElementType v9, ElementType v10, ElementType v11, ElementType v12, ElementType v13, ElementType v14, ElementType v15);
				static ValueType LoadUnaligned(const ElementType* const data);
				static ElementType GetLane(ConstRef a, int idx);
				static ValueType SetLane(ConstRef a, ElementType v, int idx);

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
			inline Int16x16::ValueType Int16x16::Load(const ElementType* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Int16x16::ValueType Int16x16::Create(
				ElementType v0, ElementType v1, ElementType v2, ElementType v3, ElementType v4, ElementType v5, ElementType v6, ElementType v7,
				ElementType v8, ElementType v9, ElementType v10, ElementType v11, ElementType v12, ElementType v13, ElementType v14, ElementType v15)
			{
				ValueType result = { {
						v0, v1, v2, v3, v4, v5, v6, v7,
						v8, v9, v10, v11, v12, v13, v14, v15
					} };
				return result;
			}

			inline Int16x16::ValueType Int16x16::LoadUnaligned(const ElementType* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline Int16x16::ElementType Int16x16::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Int16x16::ValueType Int16x16::SetLane(ConstRef a, ElementType v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Int16x16::ValueType Int16x16::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int16_t(-128) : int16_t(temp);
				}
				return result;
			}

			inline Int16x16::ValueType Int16x16::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int16_t(-128) : int16_t(temp);
				}
				return result;
			}

			inline Int16x16::ValueType Int16x16::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int8_t va = int8_t(~a.data[i]);
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Int16x16::ValueType Int16x16::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Int16x16::ValueType Int16x16::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
