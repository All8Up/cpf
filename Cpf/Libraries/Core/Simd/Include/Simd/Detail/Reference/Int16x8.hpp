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
			struct Int16x8
			{
				typedef int16_t ElementType;
				static const size_t kElementCount = 8;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(16) ValueType
				{
					int16_t data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const int16_t* const data);
				static ValueType Create(int16_t v0, int16_t v1, int16_t v2, int16_t v3, int16_t v4, int16_t v5, int16_t v6, int16_t v7);
				static ValueType LoadUnaligned(const int16_t* const data);
				static int16_t GetLane(ConstRef a, int idx);
				static ValueType SetLane(ConstRef a, int16_t v, int idx);

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
				static ValueType ZERO;
				static ValueType ONE;
			};


			//////////////////////////////////////////////////////////////////////////
			inline Int16x8::ValueType Int16x8::Load(const int16_t* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Int16x8::ValueType Int16x8::Create(int16_t v0, int16_t v1, int16_t v2, int16_t v3, int16_t v4, int16_t v5, int16_t v6, int16_t v7)
			{
				ValueType result = { {
					v0, v1, v2, v3, v4, v5, v6, v7
				} };
				return result;
			}

			inline Int16x8::ValueType Int16x8::LoadUnaligned(const int16_t* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline int16_t Int16x8::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Int16x8::ValueType Int16x8::SetLane(ConstRef a, int16_t v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Int16x8::ValueType Int16x8::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int16_t(-128) : int16_t(temp);
				}
				return result;
			}

			inline Int16x8::ValueType Int16x8::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int16_t(-128) : int16_t(temp);
				}
				return result;
			}

			inline Int16x8::ValueType Int16x8::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int16_t va = ~a.data[i];
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Int16x8::ValueType Int16x8::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Int16x8::ValueType Int16x8::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
