//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Rounding.hpp"
#include <immintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		/*
		This layer is intended to provide a type safe abstraction on top
		of the simd types.  While this is implemented in terms of VC it
		is intended to extend over to GCC/Clang and wrap the vector types
		there, which should be a bit easier.
		*/
		namespace SSE4_1
		{
#define cpf_movehl_epi32(lhs, rhs) _mm_castps_si128(_mm_movehl_ps(_mm_castsi128_ps(static_cast<__m128i>(lhs)), _mm_castsi128_ps(static_cast<__m128i>(rhs))))
#define cpf_movelh_epi32(lhs, rhs) _mm_castps_si128(_mm_movelh_ps(_mm_castsi128_ps(static_cast<__m128i>(lhs)), _mm_castsi128_ps(static_cast<__m128i>(rhs))))
#define cpf_shuffle_epi32(lhs, rhs, mask) _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(lhs), _mm_castsi128_ps(rhs), mask))

			union alignas(16) UInt32x4
			{
				uint32_t UInt32[4];
				__m128i mVector;
			};


			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, int COUNT>
			struct alignas(ALIGNMENT)I32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(16) I32x4<__m128i, 16, 4, int32_t, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = __m128i;
				static constexpr int kLanes = 4;
				using Element = int32_t;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = I32x4<Type, 16, 4, int32_t, 1>;
				using Lanes_2 = I32x4<Type, 16, 4, int32_t, 2>;
				using Lanes_3 = I32x4<Type, 16, 4, int32_t, 3>;
				using Lanes_4 = I32x4<Type, 16, 4, int32_t, 4>;

				constexpr I32x4() {}
				constexpr I32x4(Element value) : mVector(_mm_set_epi32(value, value, value, value)) {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				constexpr I32x4(Element v0, Element v1) : mVector(_mm_set_epi32(0, 0, v1, v0)) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				constexpr I32x4(Element v0, Element v1, Element v2) : mVector(_mm_set_epi32(0, v2, v1, v0)) {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				constexpr I32x4(Element v0, Element v1, Element v2, Element v3) : mVector(_mm_set_epi32(v3, v2, v1, v0)) {}

				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x4(Lanes_2 v01, Element v2)
					: mVector(cpf_shuffle_epi32(static_cast<__m128i>(v01), _mm_set_epi32(v2, 0, 0, 0), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				I32x4(Element v0, Lanes_2 v12)
					: mVector(_mm_set_epi32(0, v12.GetLane<1>(), v12.GetLane<0>(), v0))
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Lanes_2 v01, Element v2, Element v3)
					: mVector(cpf_shuffle_epi32(static_cast<__m128i>(v01), _mm_set_epi32(0, 0, v3, v2), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Element v0, Lanes_2 v12, Element v3)
				{
					auto t = cpf_movelh_epi32(_mm_set_epi32(0, 0, v3, v0), v12);
					mVector = cpf_shuffle_epi32(t, t, _MM_SHUFFLE(1, 3, 2, 0));
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Element v0, Element v1, Lanes_2 v23)
					: mVector(cpf_shuffle_epi32(_mm_set_epi32(0, 0, v1, v0), static_cast<__m128i>(v23), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Lanes_2 v01, I32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(cpf_shuffle_epi32(static_cast<__m128i>(v01), static_cast<__m128i>(v23), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Lanes_3 v012, Element v3)
				{
					auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
					auto t = _mm_and_si128(static_cast<__m128i>(v012), mask);
					auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
					mVector = a;
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				I32x4(Element v0, Lanes_3 v123)
				{
					auto t = _mm_slli_si128(static_cast<__m128i>(v123), 4);
					auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&v0)));
					mVector = a;
				}
				explicit constexpr I32x4(Type value) : mVector(value) {}

				I32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const
				{
					return _mm_cvtsi128_si32(mVector);
				}

				template <int INDEX>
				Element GetLane() const
				{
					Element result;
					_MM_EXTRACT_FLOAT(*reinterpret_cast<float*>(&result), _mm_castsi128_ps(static_cast<__m128i>(mVector)), INDEX);
					return result;
				}
				Element GetLane(int index) const
				{
					float result;
					switch (index)
					{
					case 0: _MM_EXTRACT_FLOAT(result, _mm_castsi128_ps(static_cast<__m128i>(mVector)), 0); break;
					case 1: _MM_EXTRACT_FLOAT(result, _mm_castsi128_ps(static_cast<__m128i>(mVector)), 1); break;
					case 2: _MM_EXTRACT_FLOAT(result, _mm_castsi128_ps(static_cast<__m128i>(mVector)), 2); break;
					case 3: _MM_EXTRACT_FLOAT(result, _mm_castsi128_ps(static_cast<__m128i>(mVector)), 3); break;
					default:
						result = 0.0f;
						CPF_ASSERT_ALWAYS;
					}
					return *reinterpret_cast<Element*>(&result);
				}
				void SetLane(int index, int32_t value)
				{
					switch(index)
					{
					case 0: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 0); break;
					case 1: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 1); break;
					case 2: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 2); break;
					case 3: mVector = _mm_insert_epi32(static_cast<__m128i>(mVector), value, 3); break;
					}
				}
				template <int I0, int I1>
				Type GetLanes() const
				{
					return cpf_shuffle_epi32(static_cast<__m128i>(mVector), static_cast<__m128i>(mVector), _MM_SHUFFLE(0, 0, I1, I0));
				}
				template <int I0, int I1, int I2>
				Type GetLanes() const
				{
					return cpf_shuffle_epi32(static_cast<__m128i>(mVector), static_cast<__m128i>(mVector), _MM_SHUFFLE(0, I2, I1, I0));
				}
				template <int I0, int I1, int I2, int I3>
				Type GetLanes() const
				{
					return cpf_shuffle_epi32(static_cast<__m128i>(mVector), static_cast<__m128i>(mVector), _MM_SHUFFLE(I3, I2, I1, I0));
				}

				Type mVector;
			};

			template<int COUNT>
			using I32x4_ = I32x4<__m128i, 16, 4, int32_t, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator == (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto cmp = _mm_cmpeq_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs));
				auto mask = _mm_movemask_ps(_mm_castsi128_ps(cmp));
				return I32x4_<COUNT>::kLaneMask & mask;
			}
			template <typename TYPE>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator != (const TYPE lhs, const TYPE rhs)
			{
				return (~(lhs==rhs)) & TYPE::kLaneMask;
			}
			template <typename TYPE>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator < (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kLaneMask & _mm_movemask_ps(_mm_castsi128_ps(_mm_cmplt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (const TYPE lhs, const TYPE rhs)
			{
				return (lhs < rhs) | (lhs == rhs);
			}
			template <typename TYPE>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator > (const TYPE lhs, const TYPE rhs)
			{
				return TYPE::kLaneMask & _mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs))));
			}
			template <typename TYPE>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (const TYPE lhs, const TYPE rhs)
			{
				return (lhs > rhs) | (lhs == rhs);
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator - (const I32x4_<COUNT> value)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(value));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_mul_ps(l, _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator + (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_add_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator - (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_sub_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator * (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(lhs));
				auto r = _mm_cvtepi32_ps(static_cast<__m128i>(rhs));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_mul_ps(l, r)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL operator / (const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				auto l = _mm_cvtepi32_ps(static_cast<__m128i>(lhs));
				auto r = _mm_cvtepi32_ps(static_cast<__m128i>(rhs));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_div_ps(l, r)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Min(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_min_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<2> value)
			{
				auto second = _mm_castps_si128(
					_mm_shuffle_ps(
						_mm_castsi128_ps(static_cast<__m128i>(value)),
						_mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(static_cast<__m128i>(value), second);
				return I32x4_<1>(the_low);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<3> value)
			{
				auto folded = _mm_castps_si128(_mm_movehl_ps(
					_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value))));
				auto two_low = _mm_castsi128_ps(_mm_min_epi32(static_cast<__m128i>(value), folded));
				auto second = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(_mm_castps_si128(two_low), second);
				return I32x4_<1>(the_low);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMin(const I32x4_<4> value)
			{
				auto folded = _mm_castps_si128(_mm_movehl_ps(
					_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value))));
				auto two_low = _mm_castsi128_ps(_mm_min_epi32(static_cast<__m128i>(value), folded));
				auto second = _mm_castps_si128(_mm_shuffle_ps(two_low, two_low, _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_low = _mm_min_epi32(_mm_castps_si128(two_low), second);
				return I32x4_<1>(the_low);
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Max(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				return I32x4_<COUNT>(_mm_max_epi32(static_cast<__m128i>(lhs), static_cast<__m128i>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<2> value)
			{
				auto second = _mm_castps_si128(
					_mm_shuffle_ps(
						_mm_castsi128_ps(static_cast<__m128i>(value)),
						_mm_castsi128_ps(static_cast<__m128i>(value)), _MM_SHUFFLE(0, 0, 0, 1)));
				auto the_high = _mm_max_epi32(static_cast<__m128i>(value), second);
				return I32x4_<1>(the_high);
			}
			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<3> value)
			{
				auto folded = _mm_movehl_ps(_mm_castsi128_ps(static_cast<__m128i>(value)), _mm_castsi128_ps(static_cast<__m128i>(value)));
				auto two_high = _mm_max_epi32(static_cast<__m128i>(value), _mm_castps_si128(folded));
				auto second = _mm_shuffle_ps(folded, folded, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_epi32(two_high, _mm_castps_si128(second));
				return I32x4_<1>(the_high);
			}

			template <>
			CPF_FORCE_INLINE I32x4_<1> CPF_VECTORCALL HMax(const I32x4_<4> value)
			{
				auto folded = cpf_movehl_epi32(static_cast<__m128i>(value), static_cast<__m128i>(value));
				auto two_low = _mm_max_epi32(static_cast<__m128i>(value), folded);
				auto second = cpf_shuffle_epi32(two_low, two_low, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_epi32(two_low, second);
				return I32x4_<1>(the_high);
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Sqrt(const I32x4_<COUNT> value)
			{
				auto v = _mm_cvtepi32_ps(static_cast<__m128i>(value));
				return I32x4_<COUNT>(_mm_cvttps_epi32(_mm_sqrt_ps(v)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Clamp(
				const I32x4_<COUNT> value, typename I32x4_<COUNT>::Element low, typename I32x4_<COUNT>::Element high)
			{
				return I32x4_<COUNT>(
					_mm_min_epi32(_mm_set_epi32(high, high, high, high),
						_mm_max_epi32(_mm_set_epi32(low, low, low, low), static_cast<__m128i>(value))));
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Modulus(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs)
			{
				I32x4_<COUNT> result = lhs / rhs;
				result = result * rhs;
				result = lhs - result;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE I32x4_<COUNT> CPF_VECTORCALL Abs(const I32x4_<COUNT> value)
			{
				static constexpr UInt32x4 kSignBits = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
				return I32x4_<COUNT>(_mm_andnot_si128(kSignBits.mVector, static_cast<__m128i>(value)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const I32x4_<COUNT> lhs, const I32x4_<COUNT> rhs, int32_t tolerance)
			{
				return (Abs(lhs - rhs) <= I32x4_<COUNT>(tolerance)) == I32x4_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using I32x4_1 = I32x4<__m128i, 16, 4, int32_t, 1>;
			using I32x4_2 = I32x4<__m128i, 16, 4, int32_t, 2>;
			using I32x4_3 = I32x4<__m128i, 16, 4, int32_t, 3>;
			using I32x4_4 = I32x4<__m128i, 16, 4, int32_t, 4>;
		}
	}
}
