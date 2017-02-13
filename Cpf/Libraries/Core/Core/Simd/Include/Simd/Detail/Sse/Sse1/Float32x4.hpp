//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse1
		{
			//////////////////////////////////////////////////////////////////////////
			/// Sse1 implementation of Float32x4.
			//////////////////////////////////////////////////////////////////////////
			struct Float32x4
			{
				//////////////////////////////////////////////////////////////////////////
				using ElementType = float;
				using ValueType = Float32x4_ValueType;
				using ConstRef = ValueType;

				//////////////////////////////////////////////////////////////////////////
				static const ValueType kZero;
				static const ValueType kOne;

				//////////////////////////////////////////////////////////////////////////
				static ValueType Load(const float* const data);
				static ValueType Create(float v0, float v1, float v2, float v3);
				static ValueType LoadUnaligned(const float* const data);
				static float GetLane(ConstRef a, int idx);
				static ValueType SetLane(float v, ConstRef a, int idx);

				static ValueType Splat(ConstRef value, int idx);

				static bool IsValid(ConstRef a);
				static bool Equal(ConstRef a, ConstRef b);

				static ValueType Negate3(ConstRef a);
				static ValueType Negate4(ConstRef a);

				static ValueType Add3(ConstRef a, ConstRef b);
				static ValueType Add4(ConstRef a, ConstRef b);

				static ValueType Sub3(ConstRef a, ConstRef b);
				static ValueType Sub4(ConstRef a, ConstRef b);

				static ValueType Mul4(ConstRef a, ConstRef b);
				static ValueType Div4(ConstRef a, ConstRef b);

				static ValueType Min4(ConstRef a, ConstRef b);
				static ValueType Max4(ConstRef a, ConstRef b);

				static float Dot3(ConstRef a, ConstRef b);
				static float Dot4(ConstRef a, ConstRef b);
				static float Mag3(ConstRef a);
				static ValueType Norm3(ConstRef a);
				static ValueType Norm4(ConstRef a);

				static ValueType Mod3(ConstRef a, ConstRef b);

				static ValueType Cross3(ConstRef a, ConstRef b);

				static ValueType Min3(ConstRef a, ConstRef b);
				static ValueType Max3(ConstRef a, ConstRef b);
				static ValueType Clamp3(ConstRef v, ConstRef l, ConstRef h);

				// TODO: I want a generic swizzle solution so something like the following
				// can be mapped correctly:
				// v = f32x4( a.x, b.x, a.y, b.y )	// _mm_unpacklo_ps
				// v = f32x4( a.z, b.z, a.w, b.w )	// _mm_unpackhi_ps
				// v = f32x4( a.xy, b.xy )			// _mm_movelh_ps
				// v = f32x4( b.zw, a.zw )			// _mm_movehl_ps
				// other variations would fall back to _mm_shuffle_ps
				static ValueType SpliceLow(ConstRef a, ConstRef b);
				static ValueType SpliceHigh(ConstRef a, ConstRef b);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Float32x4::ValueType Float32x4::Load(const float* const data)
			{
				return _mm_load_ps(data);
			}

			inline Float32x4::ValueType Float32x4::Create(float v0, float v1, float v2, float v3)
			{
				ValueType result = { v0, v1, v2, v3 };
				return result;
			}

			inline Float32x4::ValueType Float32x4::LoadUnaligned(const float* const data)
			{
				return _mm_loadu_ps(data);
			}

			inline float Float32x4::GetLane(ConstRef a, int idx)
			{
				float result;
				switch (idx & 3)
				{
				case 0:		_mm_store_ss(&result, a); return result;
				case 1:		_mm_store_ss(&result, _mm_shuffle_ps(a, a, 1)); return result;
				case 2:		_mm_store_ss(&result, _mm_shuffle_ps(a, a, 2)); return result;
				case 3:		_mm_store_ss(&result, _mm_shuffle_ps(a, a, 3)); return result;
				}
				return 0.0f;
			}

			inline Float32x4::ValueType Float32x4::SetLane(float v, ConstRef a, int idx)
			{
				// TODO: Switch to sse instructions to prevent flush to memory.
				ValueType result = a;
#if CPF_TARGET_WINDOWS
				result.m128_f32[idx] = v;
#elif CPF_TARGET_DARWIN
				result[idx] = v;
#endif
				return result;
			}

			inline Float32x4::ValueType Float32x4::Splat(ConstRef value, int idx)
			{
				auto v = GetLane(value, idx);
				return Float32x4::Create(v, v, v, v);
			}


			inline bool Float32x4::IsValid(ConstRef a)
			{
				ValueType test = _mm_mul_ps(a, _mm_setzero_ps());
				test = _mm_cmpeq_ps(test, _mm_setzero_ps());
				int mask = _mm_movemask_ps(test);
				return(0x0f == mask);
			}

			inline bool Float32x4::Equal(ConstRef a, ConstRef b)
			{
				ValueType test = _mm_cmpeq_ps(a, b);
				int mask = _mm_movemask_ps(test);
				return(0x0f == mask);
			}

			inline Float32x4::ValueType Float32x4::Negate3(ConstRef a)
			{
				ValueType negOnes = { -1.0f, -1.0f, -1.0f, 1.0f };
				return _mm_mul_ps(negOnes, a);
			}

			inline Float32x4::ValueType Float32x4::Negate4(ConstRef a)
			{
				ValueType negOnes = { -1.0f, -1.0f, -1.0f, -1.0f };
				return _mm_mul_ps(negOnes, a);
			}

			inline Float32x4::ValueType Float32x4::Add3(ConstRef a, ConstRef b)
			{
				ValueType wMask = { 1.0f, 1.0f, 1.0f, 0.0f };
				ValueType temp = _mm_mul_ps(a, wMask);
				return _mm_add_ps(temp, b);
			}

			inline Float32x4::ValueType Float32x4::Add4(ConstRef a, ConstRef b)
			{
				return _mm_add_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Sub3(ConstRef a, ConstRef b)
			{
				ValueType wMask = { 1.0f, 1.0f, 1.0f, 0.0f };
				ValueType temp = _mm_mul_ps(b, wMask);
				return _mm_sub_ps(a, temp);
			}

			inline Float32x4::ValueType Float32x4::Sub4(ConstRef a, ConstRef b)
			{
				return _mm_sub_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Mul4(ConstRef a, ConstRef b)
			{
				return _mm_mul_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Div4(ConstRef a, ConstRef b)
			{
				return _mm_div_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Min4(ConstRef a, ConstRef b)
			{
				return _mm_min_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Max4(ConstRef a, ConstRef b)
			{
				return _mm_max_ps(a, b);
			}

			inline float Float32x4::Dot3(ConstRef a, ConstRef b)
			{
				__m128 result = _mm_mul_ps(a, b);
				__m128 p1 = _mm_movehl_ps(result, result); // Move z(2) component into x(0).

				// Add horizontally.
				__m128 a1 = _mm_add_ps(result, p1);

				__m128 p2 = _mm_shuffle_ps(result, result, _MM_SHUFFLE(1, 3, 3, 1)); // Move y(1) component into x(0).
				result = _mm_add_ps(a1, p2);

				// Save the results to a float.
				float sresult;
				_mm_store_ss(&sresult, result);

				return sresult;
			}

			inline float Float32x4::Dot4(ConstRef a, ConstRef b)
			{
				__m128 result = _mm_mul_ps(a, b);
				__m128 p1 = _mm_movehl_ps(result, result); // Move z(2) & w(3) component into x(0) & y(1).

				// Add horizontally.
				__m128 a1 = _mm_add_ps(result, p1);

				__m128 p2 = _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(0, 0, 0, 1)); // Move y(1) component into x(0).
				result = _mm_add_ps(a1, p2);

				// Save the results to a float.
				float sresult;
				_mm_store_ss(&sresult, result);

				return sresult;
			}

			inline float Float32x4::Mag3(ConstRef a)
			{
				__m128 result = _mm_mul_ps(a, a);
				__m128 p1 = _mm_movehl_ps(result, result); // Move z(2) component into x(0).

				// Add horizontally.
				__m128 a1 = _mm_add_ps(result, p1);

				__m128 p2 = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 3, 3, 1)); // Move y(1) component into x(0).
				result = _mm_add_ps(a1, p2);

				result = _mm_sqrt_ss(result);

				float sresult;
				_mm_store_ss(&sresult, result);

				return sresult;
			}

			inline Float32x4::ValueType Float32x4::Norm3(ConstRef a)
			{
				__m128 result = _mm_mul_ps(a, a);
				__m128 p1 = _mm_movehl_ps(result, result); // Move z(2) component into x(0).
				__m128 p2 = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 3, 3, 1)); // Move y(1) component into x(0).

				// Add horizontally.
				__m128 a1 = _mm_add_ps(result, p1);
				result = _mm_add_ps(a1, p2);
				result = _mm_sqrt_ss(result);

				result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(0, 0, 0, 0));

				result = _mm_div_ps(a, result);

				return result;
			}

			inline Float32x4::ValueType Float32x4::Norm4(ConstRef /* a */)
			{
				// TODO
				return Float32x4::kZero;
			}

			inline Float32x4::ValueType Float32x4::Mod3(ConstRef a, ConstRef b)
			{
				__m128 c = _mm_div_ps(a, b);
				__m128i i = _mm_cvttps_epi32(c);
				__m128 ct = _mm_cvtepi32_ps(i);
				__m128 bs = _mm_mul_ps(ct, b);
				__m128 r = _mm_sub_ps(a, bs);
				return r;
			}

			inline Float32x4::ValueType Float32x4::Cross3(ConstRef a, ConstRef b)
			{
				static const int swizzle1 = _MM_SHUFFLE(3, 0, 2, 1);
				static const int swizzle2 = _MM_SHUFFLE(3, 1, 0, 2);

				__m128 v1 = _mm_shuffle_ps(a, a, swizzle1);
				__m128 v2 = _mm_shuffle_ps(b, b, swizzle2);
				__m128 v3 = _mm_shuffle_ps(a, a, swizzle2);
				__m128 v4 = _mm_shuffle_ps(b, b, swizzle1);

				__m128 p1 = _mm_mul_ps(v1, v2);
				__m128 p2 = _mm_mul_ps(v3, v4);

				__m128 result = _mm_sub_ps(p1, p2);
				return result;
			}

			inline Float32x4::ValueType Float32x4::Min3(ConstRef a, ConstRef b)
			{
				return _mm_min_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Max3(ConstRef a, ConstRef b)
			{
				return _mm_max_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::Clamp3(ConstRef v, ConstRef l, ConstRef h)
			{
				return Min3(Max3(v, l), h);
			}

			inline Float32x4::ValueType Float32x4::SpliceLow(ConstRef a, ConstRef b)
			{
				return _mm_unpacklo_ps(a, b);
			}

			inline Float32x4::ValueType Float32x4::SpliceHigh(ConstRef a, ConstRef b)
			{
				return _mm_unpackhi_ps(a, b);
			}
		}
	}
}
