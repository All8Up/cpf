//////////////////////////////////////////////////////////////////////////
template <typename T>
class Test_Float32x8 : public::testing::Test
{
public:
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types<
	Cpf::Simd::Reference::Float32x8
#if CPF_SIMD_AVX2
	, Cpf::Simd::Avx2::Float32x8
#endif
#if CPF_SIMD_AVX
	, Cpf::Simd::Avx::Float32x8
#endif
#if CPF_SIMD_SSE4a
	, Cpf::Simd::Sse4a::Float32x8
#endif
#if CPF_SIMD_SSE4_2
	, Cpf::Simd::Sse4_2::Float32x8
#endif
#if CPF_SIMD_SSE4_1
	, Cpf::Simd::Sse4_1::Float32x8
#endif
#if CPF_SIMD_SSE3
	, Cpf::Simd::Sse3::Float32x8
#endif
#if CPF_SIMD_SSE2
	, Cpf::Simd::Sse2::Float32x8
#endif
#if CPF_SIMD_SSE1
	, Cpf::Simd::Sse1::Float32x8
#endif
> Float32x8_Types;
TYPED_TEST_CASE(Test_Float32x8, Float32x8_Types);
