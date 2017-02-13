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
			struct Int8x32
			{
				typedef int8_t ElementType;
				static const size_t kElementCount = 32;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(32) ValueType
				{
					int8_t data[kElementCount];
				};
				typedef ValueType const& ConstRef;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const int8_t* const data);
				static ValueType Create(int8_t v0, int8_t v1, int8_t v2, int8_t v3, int8_t v4, int8_t v5, int8_t v6, int8_t v7, int8_t v8, int8_t v9, int8_t v10, int8_t v11, int8_t v12, int8_t v13, int8_t v14, int8_t v15);
				static ValueType LoadUnaligned(const int8_t* const data);
				static int8_t GetLane(ConstRef a, int idx);
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
			inline Int8x32::ValueType Int8x32::Load(const int8_t* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Int8x32::ValueType Int8x32::Create(int8_t v0, int8_t v1, int8_t v2, int8_t v3, int8_t v4, int8_t v5, int8_t v6, int8_t v7, int8_t v8, int8_t v9, int8_t v10, int8_t v11, int8_t v12, int8_t v13, int8_t v14, int8_t v15)
			{
				ValueType result = { {
						v0, v1, v2, v3, v4, v5, v6, v7,
						v8, v9, v10, v11, v12, v13, v14, v15
					} };
				return result;
			}

			inline Int8x32::ValueType Int8x32::LoadUnaligned(const int8_t* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline int8_t Int8x32::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Int8x32::ValueType Int8x32::SetLane(ConstRef a, int8_t v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Int8x32::ValueType Int8x32::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int8_t(-128) : int8_t(temp);
				}
				return result;
			}

			inline Int8x32::ValueType Int8x32::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? int8_t(-128) : int8_t(temp);
				}
				return result;
			}

			inline Int8x32::ValueType Int8x32::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int8_t va = ~a.data[i];
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Int8x32::ValueType Int8x32::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Int8x32::ValueType Int8x32::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
