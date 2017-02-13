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
			struct Uint8x16
			{
				typedef uint8_t ElementType;
				static const size_t kElementCount = 16;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(16) ValueType
				{
					uint8_t data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const uint8_t* const data);
				static ValueType Create(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);
				static ValueType LoadUnaligned(const uint8_t* const data);
				static uint8_t GetLane(ConstRef a, int idx);
				static ValueType SetLane(ConstRef a, uint8_t v, int idx);

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
			inline Uint8x16::ValueType Uint8x16::Load(const uint8_t* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Create(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15)
			{
				ValueType result = { {
						v0, v1, v2, v3, v4, v5, v6, v7,
						v8, v9, v10, v11, v12, v13, v14, v15
					} };
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::LoadUnaligned(const uint8_t* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline uint8_t Uint8x16::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Uint8x16::ValueType Uint8x16::SetLane(ConstRef a, uint8_t v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 255 ? uint8_t(255) : uint8_t(temp);
				}
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? uint8_t(127) : temp <= -128 ? uint8_t(-128) : uint8_t(temp);
				}
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					uint8_t va = ~a.data[i];
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Uint8x16::ValueType Uint8x16::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
