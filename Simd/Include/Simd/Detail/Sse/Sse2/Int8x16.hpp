//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse2
		{
			struct Int8x16
			{
				//////////////////////////////////////////////////////////////////////////
				using ValueType = Int8x16_ValueType;
				using ConstRef = ValueType;

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
			inline Int8x16::ValueType Int8x16::Load(const int8_t* const data)
			{
				return _mm_load_si128(reinterpret_cast<const __m128i*>(data));
			}

			inline Int8x16::ValueType Int8x16::Create(int8_t v0, int8_t v1, int8_t v2, int8_t v3, int8_t v4, int8_t v5, int8_t v6, int8_t v7, int8_t v8, int8_t v9, int8_t v10, int8_t v11, int8_t v12, int8_t v13, int8_t v14, int8_t v15)
			{
				ValueType result = {
					v0, v1, v2, v3, v4, v5, v6, v7,
					v8, v9, v10, v11, v12, v13, v14, v15
				};
				return result;
			}


			inline Int8x16::ValueType Int8x16::LoadUnaligned(const int8_t* const data)
			{
				return _mm_loadu_si128(reinterpret_cast<const __m128i*>(data));
			}

			inline int8_t Int8x16::GetLane(ConstRef a, int idx)
			{
				float value;
				ValueType temp;

				switch (idx >> 2)
				{
				case 0:
					_mm_store_ss(&value, _mm_castsi128_ps(a));
					return reinterpret_cast<const int8_t*>(&value)[idx & 3];
				case 1: temp = _mm_shuffle_epi32(a, 1); break;
				case 2: temp = _mm_shuffle_epi32(a, 2); break;
				case 3: temp = _mm_shuffle_epi32(a, 3); break;
				}
				_mm_store_ss(&value, _mm_castsi128_ps(temp));
				return reinterpret_cast<const int8_t*>(&value)[idx & 3];
			}

			inline Int8x16::ValueType Int8x16::SetLane(ConstRef a, int8_t v, int idx)
			{
				// TODO: Switch to sse instructions to prevent flush to memory.
				ValueType result = a;
#if CPF_TARGET_WINDOWS
				result.m128i_i8[idx] = v;
#elif CPF_TARGET_DARWIN
				result[idx] = v;
#endif
				return result;
			}

			inline Int8x16::ValueType Int8x16::Add(ConstRef a, ConstRef b)
			{
				return _mm_add_epi8(a, b);
			}

			inline Int8x16::ValueType Int8x16::AddSaturate(ConstRef a, ConstRef b)
			{
				return _mm_adds_epi8(a, b);
			}

			inline Int8x16::ValueType Int8x16::Sub(ConstRef a, ConstRef b)
			{
				return _mm_sub_epi8(a, b);
			}

			inline Int8x16::ValueType Int8x16::SubSaturate(ConstRef a, ConstRef b)
			{
				return _mm_subs_epi8(a, b);
			}

			inline Int8x16::ValueType Int8x16::And(ConstRef a, ConstRef b)
			{
				return _mm_and_si128(a, b);
			}

			inline Int8x16::ValueType Int8x16::AndNot(ConstRef a, ConstRef b)
			{
				return _mm_andnot_si128(a, b);
			}

			inline Int8x16::ValueType Int8x16::Or(ConstRef a, ConstRef b)
			{
				return _mm_or_si128(a, b);
			}

			inline Int8x16::ValueType Int8x16::Xor(ConstRef a, ConstRef b)
			{
				return _mm_xor_si128(a, b);
			}

			inline Int8x16::ValueType Int8x16::Min(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < 16; ++i)
#if CPF_TARGET_WINDOWS
					result.m128i_i8[i] = a.m128i_i8[i] < b.m128i_i8[i] ? a.m128i_i8[i] : b.m128i_i8[i];
#elif CPF_TARGET_DARWIN
					result[i] = a[i] < b[i] ? a[i] : b[i];
#endif
				return result;
			}

			inline Int8x16::ValueType Int8x16::Max(ConstRef a, ConstRef b)
			{
				ValueType result;
				for (int i = 0; i < 16; ++i)
#if CPF_TARGET_WINDOWS
					result.m128i_i8[i] = a.m128i_i8[i] > b.m128i_i8[i] ? a.m128i_i8[i] : b.m128i_i8[i];
#elif CPF_TARGET_DARWIN
					result[i] = a[i] > b[i] ? a[i] : b[i];
#endif
				return result;
			}
		}
	}
}
