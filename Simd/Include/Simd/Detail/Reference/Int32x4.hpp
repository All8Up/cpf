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
			struct Int32x4
			{
				using ElementType = int32_t;
				static const size_t kElementCount = 4;

				//////////////////////////////////////////////////////////////////////////
				struct CPF_ALIGN(16) ValueType
				{
					int32_t data[4];
				};
				using ConstRef = ValueType const&;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const int32_t* const data);
				static ValueType Create(int32_t v0, int32_t v1, int32_t v2, int32_t v3);
				static ValueType LoadUnaligned(const int32_t* const data);
				static int32_t GetLane(ConstRef a, int idx);
				static ValueType SetLane(ConstRef a, int32_t v, int idx);

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
			inline Int32x4::ValueType Int32x4::Load(const int32_t* const data)
			{
				ValueType result;
				const uint64_t* const d64 = reinterpret_cast<const uint64_t* const>(data);
				*reinterpret_cast<uint64_t*>(result.data) = d64[0];
				*reinterpret_cast<uint64_t*>(result.data + 8) = d64[1];
				return result;
			}

			inline Int32x4::ValueType Int32x4::Create(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
			{
				ValueType result = { {
					v0, v1, v2, v3
				} };
				return result;
			}

			inline Int32x4::ValueType Int32x4::LoadUnaligned(const int32_t* const data)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = data[i];
				return result;
			}

			inline int32_t Int32x4::GetLane(ConstRef a, int idx)
			{
				return a.data[idx];
			}

			inline Int32x4::ValueType Int32x4::SetLane(ConstRef a, int32_t v, int idx)
			{
				ValueType result = a;
				result.data[idx] = v;
				return result;
			}

			inline Int32x4::ValueType Int32x4::Add(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] + b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::AddSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) + int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? -128 : temp;
				}
				return result;
			}

			inline Int32x4::ValueType Int32x4::Sub(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] - b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::SubSaturate(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int temp = int(a.data[i]) - int(b.data[i]);
					result.data[i] = temp >= 127 ? 127 : temp <= -128 ? -128 : temp;
				}
				return result;
			}

			inline Int32x4::ValueType Int32x4::And(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] & b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::AndNot(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
				{
					int32_t va = ~a.data[i];
					result.data[i] = va & b.data[i];
				}
				return result;
			}

			inline Int32x4::ValueType Int32x4::Or(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] | b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::Xor(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] ^ b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] <= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}

			inline Int32x4::ValueType Int32x4::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < kElementCount; ++i)
					result.data[i] = a.data[i] >= b.data[i] ? a.data[i] : b.data[i];
				return result;
			}
		}
	}
}
