//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <emmintrin.h>
#include <smmintrin.h>

namespace Cpf
{
	namespace SIMD
	{
		/*
		This layer is intended to provide a type safe abstraction on top
		of the simd types.  While this is implemented in terms of VC it
		is intended to extend over to GCC/Clang and wrap the vector types
		there, which should be a bit easier.
		TODO: There are plenty of optimizations to do here, this is a rough
		first pass.
		*/
		namespace SSE4_1
		{
			template <typename TYPE, int ALIGNMENT, int LANES, typename ELEMENT, int COUNT>
			struct alignas(ALIGNMENT) F32x4;

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(16) F32x4<__m128, 16, 4, float, COUNT>
			{
				static constexpr int kAlignment = 16;
				using Type = __m128;
				static constexpr int kLanes = 4;
				using Element = float;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = F32x4<__m128, 16, 4, float, 1>;
				using Lanes_2 = F32x4<__m128, 16, 4, float, 2>;
				using Lanes_3 = F32x4<__m128, 16, 4, float, 3>;
				using Lanes_4 = F32x4<__m128, 16, 4, float, 4>;

				constexpr F32x4() {}
				constexpr F32x4(Element value) : mVector{ value, value, value, value } {}
				template <typename = std::enable_if<COUNT == 2, Element>::type>
				constexpr F32x4(Element v0, Element v1) : mVector(_mm_set_ps(0.0f, 0.0f, v1, v0)) {}
				template <typename = std::enable_if<COUNT == 3, Element>::type>
				constexpr F32x4(Element v0, Element v1, Element v2) : mVector(_mm_set_ps(0.0f, v2, v1, v0)) {}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				constexpr F32x4(Element v0, Element v1, Element v2, Element v3) : mVector(_mm_set_ps(v3, v2, v1, v0)) {}

				template <typename = std::enable_if<COUNT == 3, Element>::type>
				constexpr F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2)
					: mVector(_mm_shuffle_ps(static_cast<__m128>(v01), _mm_set_ps(v2, 0, 0, 0), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				constexpr F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, Element v2, Element v3)
					: mVector(_mm_shuffle_ps(static_cast<__m128>(v01), _mm_set_ps(0, 0, v3, v2), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(float v0, F32x4<Type, kAlignment, kLanes, Element, 2> v12, Element v3)
				{
					auto t = _mm_movelh_ps(_mm_set_ps(0, 0, v3, v0), static_cast<__m128>(v12));
					mVector = _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 3, 2, 0));
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(float v0, float v1, F32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(_mm_shuffle_ps(_mm_set_ps(0, 0, v1, v0), static_cast<__m128>(v23), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 2> v01, F32x4<Type, kAlignment, kLanes, Element, 2> v23)
					: mVector(_mm_shuffle_ps(static_cast<__m128>(v01), static_cast<__m128>(v23), _MM_SHUFFLE(1, 0, 1, 0)))
				{
				}

				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(F32x4<Type, kAlignment, kLanes, Element, 3> v012, Element v3)
				{
					auto mask = _mm_set_epi32(0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
					auto t = _mm_and_si128(_mm_castps_si128(static_cast<__m128>(v012)), mask);
					auto a = _mm_or_si128(t, _mm_set_epi32(*reinterpret_cast<int*>(&v3), 0, 0, 0));
					mVector = _mm_castsi128_ps(a);
				}
				template <typename = std::enable_if<COUNT == 4, Element>::type>
				F32x4(Element v0, F32x4<Type, kAlignment, kLanes, Element, 3> v123)
				{
					auto t = _mm_slli_si128(_mm_castps_si128(static_cast<__m128>(v123)), 4);
					auto a = _mm_or_si128(t, _mm_set_epi32(0, 0, 0, *reinterpret_cast<int*>(&v0)));
					mVector = _mm_castsi128_ps(a);
				}

				explicit constexpr F32x4(Type value) : mVector(value) {}

				F32x4& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const { Element result; _mm_store_ss(&result, mVector); return result; }

				template <int INDEX>
				Element GetLane() const
				{
					Element result;
					_MM_EXTRACT_FLOAT(result, mVector, INDEX);
					return result;
				}
				Element GetLane(int index) const
				{
					Element result;
					switch (index)
					{
					case 0: _MM_EXTRACT_FLOAT(result, mVector, 0); break;
					case 1: _MM_EXTRACT_FLOAT(result, mVector, 1); break;
					case 2: _MM_EXTRACT_FLOAT(result, mVector, 2); break;
					case 3: _MM_EXTRACT_FLOAT(result, mVector, 3); break;
					default:
						result = 0.0f;
						CPF_ASSERT_ALWAYS;
					}
					return result;
				}
				void SetLane(int index, float value)
				{
					switch (index)
					{
					case 0: mVector = _mm_insert_ps(static_cast<__m128>(mVector), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 0, 0)); break;
					case 1: mVector = _mm_insert_ps(static_cast<__m128>(mVector), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 1, 0)); break;
					case 2: mVector = _mm_insert_ps(static_cast<__m128>(mVector), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 2, 0)); break;
					case 3: mVector = _mm_insert_ps(static_cast<__m128>(mVector), _mm_set_ps(value, value, value, value), _MM_MK_INSERTPS_NDX(0, 3, 0)); break;
					}
				}
				template <int I0, int I1, int I2>
				Type GetLanes() const
				{
					return _mm_shuffle_ps(static_cast<__m128>(mVector), static_cast<__m128>(mVector), _MM_SHUFFLE(0, I2, I1, I0));
				}

				Type mVector;
			};

			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			using F32x4_ = F32x4<__m128, 16, 4, float, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator == (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmpeq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator != (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmpneq_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator < (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmplt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator <= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmple_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator > (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmpgt_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE int CPF_VECTORCALL operator >= (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>::kLaneMask & _mm_movemask_ps(_mm_cmpge_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator - (const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_mul_ps(static_cast<__m128>(value), _mm_set_ps(-1.0f, -1.0f, -1.0f, -1.0f)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator + (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_add_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator - (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_sub_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator * (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_mul_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL operator / (const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Min(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_min_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}

			template <int COUNT>
			CPF_FORCE_INLINE float CPF_VECTORCALL HMin(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE float CPF_VECTORCALL HMin(const F32x4_<2> value)
			{
				auto second = _mm_shuffle_ps(static_cast<__m128>(value), static_cast<__m128>(value), _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_min_ss(static_cast<__m128>(value), second);
				float result;
				_mm_store_ss(&result, the_low);
				return result;
			}
			template <>
			CPF_FORCE_INLINE float CPF_VECTORCALL HMin(const F32x4_<4> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_low = _mm_min_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(two_low, two_low, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_low = _mm_min_ss(two_low, second);
				float result;
				_mm_store_ss(&result, the_low);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Max(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				return F32x4_<COUNT>(_mm_max_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE float CPF_VECTORCALL HMax(const F32x4_<COUNT> value)
			{
				auto folded = _mm_movehl_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto two_high = _mm_max_ps(static_cast<__m128>(value), folded);
				auto second = _mm_shuffle_ps(two_high, two_high, _MM_SHUFFLE(0, 0, 0, 1));
				auto the_high = _mm_max_ss(two_high, second);
				float result;
				_mm_store_ss(&result, the_high);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Sqrt(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_sqrt_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Reciprocal(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_rcp_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL RSqrt(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_rsqrt_ps(static_cast<__m128>(value)));
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Clamp(const F32x4_<COUNT> value, typename F32x4_<COUNT>::Element low, typename F32x4_<COUNT>::Element high)
			{
				return F32x4_<COUNT>(
					_mm_min_ps(static_cast<__m128>(
						_mm_set_ps(high, high, high, high)),
						_mm_max_ps(_mm_set_ps(low, low, low, low), static_cast<__m128>(value))));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<2>::Element CPF_VECTORCALL Dot(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs);

			template <>
			CPF_FORCE_INLINE typename F32x4_<2>::Element CPF_VECTORCALL Dot(const F32x4_<2> lhs, const F32x4_<2> rhs)
			{
				typename F32x4_<2>::Element result;
				auto mul = _mm_mul_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs));
				auto yin0 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(0, 0, 0, 1));
				auto add = _mm_add_ps(mul, yin0);
				_mm_store_ss(&result, add);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::Element CPF_VECTORCALL Magnitude(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE typename F32x4_<2>::Element CPF_VECTORCALL Magnitude(const F32x4_<2> value)
			{
				typename F32x4_<2>::Element result;
				auto mul = _mm_mul_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto yin0 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(0, 0, 0, 1));
				auto add = _mm_add_ps(mul, yin0);
				add = _mm_sqrt_ss(add);
				_mm_store_ss(&result, add);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x4_<COUNT>::Element CPF_VECTORCALL MagnitudeSq(const F32x4_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Normalize(const F32x4_<COUNT> value);

			template <>
			CPF_FORCE_INLINE F32x4_<2> CPF_VECTORCALL Normalize(const F32x4_<2> value)
			{
				auto mul = _mm_mul_ps(static_cast<__m128>(value), static_cast<__m128>(value));
				auto yin0 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(0, 0, 0, 1));
				auto len = _mm_add_ps(mul, yin0);
				len = _mm_sqrt_ss(len);
				len = _mm_shuffle_ps(len, len, _MM_SHUFFLE(0, 0, 0, 0));
				len = _mm_div_ps(static_cast<__m128>(value), len);
				return F32x4_<2>(len);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Round(const F32x4_<COUNT> value, Rounding mode)
			{
				auto oldMode = _mm_getcsr();
				switch (mode)
				{
				case Rounding::eCurrent: break;
				case Rounding::eTruncate: _mm_setcsr((oldMode&~_MM_ROUND_MASK) | _MM_ROUND_TOWARD_ZERO); break;
				case Rounding::eNearest: _mm_setcsr((oldMode&~_MM_ROUND_MASK) | _MM_ROUND_NEAREST);  break;
				case Rounding::eDown: _mm_setcsr((oldMode&~_MM_ROUND_MASK) | _MM_ROUND_DOWN);  break;
				case Rounding::eUp: _mm_setcsr((oldMode&~_MM_ROUND_MASK) | _MM_ROUND_UP); break;
				}
				auto intValue = _mm_cvtps_epi32(static_cast<__m128>(value));
				auto result = _mm_cvtepi32_ps(intValue);

				_mm_setcsr(oldMode);
				return F32x4_<COUNT>(result);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Floor(const F32x4_<COUNT> value)
			{
				return Round(value, Rounding::eDown);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Ceil(const F32x4_<COUNT> value)
			{
				return Round(value, Rounding::eUp);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Modulus(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs)
			{
				__m128 c = _mm_div_ps(static_cast<__m128>(lhs), static_cast<__m128>(rhs));
				__m128i i = _mm_cvttps_epi32(c);
				__m128 ct = _mm_cvtepi32_ps(i);
				__m128 bs = _mm_mul_ps(ct, static_cast<__m128>(rhs));
				__m128 r = _mm_sub_ps(static_cast<__m128>(lhs), bs);
				return F32x4_<COUNT>(r);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x4_<COUNT> CPF_VECTORCALL Abs(const F32x4_<COUNT> value)
			{
				return F32x4_<COUNT>(_mm_andnot_ps(_mm_castsi128_ps(_mm_set_epi32(0x80000000, 0x80000000, 0x80000000, 0x80000000)), static_cast<__m128>(value)));
			}

			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const float lhs, const float rhs, float tolerance)
			{
				return std::fabs(lhs - rhs) <= tolerance;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Near(const F32x4_<COUNT> lhs, const F32x4_<COUNT> rhs, float tolerance)
			{
				return (Abs(lhs - rhs) <= F32x4_<COUNT>(tolerance)) == F32x4_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool CPF_VECTORCALL Valid(const F32x4_<COUNT> value)
			{
				F32x4_<COUNT> test(_mm_mul_ps(static_cast<__m128>(value), _mm_setzero_ps()));
				test = _mm_cmpeq_ps(static_cast<__m128>(test), _mm_setzero_ps());
				int mask = _mm_movemask_ps(static_cast<__m128>(test));
				return(F32x4_<COUNT>::kLaneMask == (mask & F32x4_<COUNT>::kLaneMask));
			}


			//////////////////////////////////////////////////////////////////////////
			using F32x4_1 = F32x4<__m128, 16, 4, float, 1>;
			using F32x4_2 = F32x4<__m128, 16, 4, float, 2>;
			using F32x4_3 = F32x4<__m128, 16, 4, float, 3>;
			using F32x4_4 = F32x4<__m128, 16, 4, float, 4>;
		}
	}
}
