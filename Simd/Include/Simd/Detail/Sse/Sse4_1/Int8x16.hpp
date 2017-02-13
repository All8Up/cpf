//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse4_1
		{
			struct Int8x16 : public Sse3::Int8x16
			{
				static ValueType SetLane(ConstRef a, int8_t v, int idx);

				static ValueType Min(ConstRef a, ConstRef b);
				static ValueType Max(ConstRef a, ConstRef b);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Int8x16::ValueType Int8x16::SetLane(ConstRef a, int8_t v, int idx)
			{
				switch (idx)
				{
				case 0: return _mm_insert_epi8(a, v, 0);
				case 1: return _mm_insert_epi8(a, v, 1);
				case 2: return _mm_insert_epi8(a, v, 2);
				case 3: return _mm_insert_epi8(a, v, 3);
				case 4: return _mm_insert_epi8(a, v, 4);
				case 5: return _mm_insert_epi8(a, v, 5);
				case 6: return _mm_insert_epi8(a, v, 6);
				case 7: return _mm_insert_epi8(a, v, 7);
				case 8: return _mm_insert_epi8(a, v, 8);
				case 9: return _mm_insert_epi8(a, v, 9);
				case 10: return _mm_insert_epi8(a, v, 10);
				case 11: return _mm_insert_epi8(a, v, 11);
				case 12: return _mm_insert_epi8(a, v, 12);
				case 13: return _mm_insert_epi8(a, v, 13);
				case 14: return _mm_insert_epi8(a, v, 14);
				case 15: return _mm_insert_epi8(a, v, 15);
				}
				CPF_ASSERT_ALWAYS;
				return kZero;
			}

			inline Int8x16::ValueType Int8x16::Min(ConstRef a, ConstRef b)
			{
				return _mm_min_epi8(a, b);
			}

			inline Int8x16::ValueType Int8x16::Max(ConstRef a, ConstRef b)
			{
				return _mm_max_epi8(a, b);
			}
		}
	}
}
