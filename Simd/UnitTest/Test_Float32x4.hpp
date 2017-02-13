//////////////////////////////////////////////////////////////////////////
template <typename T>
class Test_Float32x4 : public::testing::Test
{
public:
	float ones[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	float series[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types<
	Cpf::Simd::Reference::Float32x4
#if CPF_SIMD_AVX2
	, Cpf::Simd::Avx2::Float32x4
#endif
#if CPF_SIMD_AVX
	, Cpf::Simd::Avx::Float32x4
#endif
#if CPF_SIMD_SSE4a
	, Cpf::Simd::Sse4a::Float32x4
#endif
#if CPF_SIMD_SSE4_2
	, Cpf::Simd::Sse4_2::Float32x4
#endif
#if CPF_SIMD_SSE4_1
	, Cpf::Simd::Sse4_1::Float32x4
#endif
#if CPF_SIMD_SSE3
	, Cpf::Simd::Sse3::Float32x4
#endif
#if CPF_SIMD_SSE2
	, Cpf::Simd::Sse2::Float32x4
#endif
#if CPF_SIMD_SSE1
	, Cpf::Simd::Sse1::Float32x4
#endif
> Float32x4_Types;
TYPED_TEST_CASE(Test_Float32x4, Float32x4_Types);


//////////////////////////////////////////////////////////////////////////
TYPED_TEST(Test_Float32x4, LoadAndAccess)
{
	typename TypeParam::ValueType a = TypeParam::Load(Test_Float32x4<TypeParam>::series);
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(a, 0));
	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(a, 1));
	EXPECT_FLOAT_EQ(3.0f, TypeParam::GetLane(a, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(a, 3));
}

TYPED_TEST(Test_Float32x4, LoadUnalignedAndAccess)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Float32x4<TypeParam>::series);
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(a, 0));
	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(a, 1));
	EXPECT_FLOAT_EQ(3.0f, TypeParam::GetLane(a, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(a, 3));
}

TYPED_TEST(Test_Float32x4, CreateAndAccess)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(a, 0));
	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(a, 1));
	EXPECT_FLOAT_EQ(3.0f, TypeParam::GetLane(a, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(a, 3));
}

TYPED_TEST(Test_Float32x4, SetLane)
{
	typename TypeParam::ValueType a = TypeParam::Create(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 4; ++i)
		a = TypeParam::SetLane(float(i), a, i);
	for (int i = 0; i < 4; ++i)
		EXPECT_FLOAT_EQ(float(i), TypeParam::GetLane(a, i));
}

TYPED_TEST(Test_Float32x4, Negate3)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Negate3(a);

	EXPECT_FLOAT_EQ(-1.0f, TypeParam::GetLane(b, 0));
	EXPECT_FLOAT_EQ(-2.0f, TypeParam::GetLane(b, 1));
	EXPECT_FLOAT_EQ(-3.0f, TypeParam::GetLane(b, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(b, 3));
}

TYPED_TEST(Test_Float32x4, Negate4)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Negate4(a);

	EXPECT_FLOAT_EQ(-1.0f, TypeParam::GetLane(b, 0));
	EXPECT_FLOAT_EQ(-2.0f, TypeParam::GetLane(b, 1));
	EXPECT_FLOAT_EQ(-3.0f, TypeParam::GetLane(b, 2));
	EXPECT_FLOAT_EQ(-4.0f, TypeParam::GetLane(b, 3));
}

TYPED_TEST(Test_Float32x4, Add3)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Add3(a, b);

	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(6.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Add4)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Add4(a, b);

	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(6.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(8.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Sub3)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Sub3(a, b);

	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Sub4)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Sub4(a, b);

	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(0.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Mul4)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Mul4(a, b);

	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(9.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(16.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Div4)
{
	typename TypeParam::ValueType a = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Div4(a, b);

	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Min4)
{
	typename TypeParam::ValueType a = TypeParam::Create(5.0f, 5.0f, 5.0f, 5.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Min4(a, b);

	EXPECT_FLOAT_EQ(1.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(2.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(3.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(4.0f, TypeParam::GetLane(c, 3));
}

TYPED_TEST(Test_Float32x4, Max4)
{
	typename TypeParam::ValueType a = TypeParam::Create(5.0f, 5.0f, 5.0f, 5.0f);
	typename TypeParam::ValueType b = TypeParam::Create(1.0f, 2.0f, 3.0f, 4.0f);
	typename TypeParam::ValueType c = TypeParam::Max4(a, b);

	EXPECT_FLOAT_EQ(5.0f, TypeParam::GetLane(c, 0));
	EXPECT_FLOAT_EQ(5.0f, TypeParam::GetLane(c, 1));
	EXPECT_FLOAT_EQ(5.0f, TypeParam::GetLane(c, 2));
	EXPECT_FLOAT_EQ(5.0f, TypeParam::GetLane(c, 3));
}
