//////////////////////////////////////////////////////////////////////////
template <typename T>
class Test_Int8x16 : public::testing::Test
{
public:

	int8_t i8x16_1[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int8_t i8x16_2[16] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	int8_t i8x16_3[16] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	int8_t i8_16_64[16] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 };
	int8_t i8_16_75[16] = { 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75 };
	int8_t i8_16_Neg64[16] = { -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64, -64 };
	int8_t i8_16_Neg75[16] = { -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75, -75 };
	int8_t i8x16_0to15[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types<
	Cpf::Simd::Reference::Int8x16
#if CPF_SIMD_AVX2
	, Cpf::Simd::Avx2::Int8x16
#endif
#if CPF_SIMD_AVX
	, Cpf::Simd::Avx::Int8x16
#endif
#if CPF_SIMD_SSE4a
	, Cpf::Simd::Sse4a::Int8x16
#endif
#if CPF_SIMD_SSE4_2
	, Cpf::Simd::Sse4_2::Int8x16
#endif
#if CPF_SIMD_SSE4_1
	, Cpf::Simd::Sse4_1::Int8x16
#endif
#if CPF_SIMD_SSE3
	, Cpf::Simd::Sse3::Int8x16
#endif
#if CPF_SIMD_SSE2
	, Cpf::Simd::Sse2::Int8x16
#endif
#if CPF_SIMD_SSE1
	, Cpf::Simd::Sse1::Int8x16
#endif
> Int8x16_Types;
TYPED_TEST_CASE(Test_Int8x16, Int8x16_Types);


//////////////////////////////////////////////////////////////////////////
TYPED_TEST(Test_Int8x16, LoadUnaligned)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(a, i), 1);

	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_0to15);
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(b, i), i);
}

TYPED_TEST(Test_Int8x16, GetLane_SetLane)
{
	typename TypeParam::ValueType a = TypeParam::kZero;
	for (int i = 0; i < 16; ++i)
	{
		a = TypeParam::SetLane(a, i, i);
	}
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(a, i), i);
}

TYPED_TEST(Test_Int8x16, Add)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_2);
	typename TypeParam::ValueType c = TypeParam::Add(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 3);
}

TYPED_TEST(Test_Int8x16, AddSaturate)
{
	typename TypeParam::ValueType a = TypeParam::AddSaturate(TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_64), TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_75));
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(a, i), 127);

	typename TypeParam::ValueType b = TypeParam::AddSaturate(TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_Neg64), TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_Neg75));
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(b, i), -128);
}

TYPED_TEST(Test_Int8x16, Sub)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_2);
	typename TypeParam::ValueType c = TypeParam::Sub(b, a);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 1);
}

TYPED_TEST(Test_Int8x16, SubSaturate)
{
	typename TypeParam::ValueType a = TypeParam::SubSaturate(TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_Neg64), TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_75));
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(a, i), -128);

	typename TypeParam::ValueType b = TypeParam::SubSaturate(TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_64), TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_Neg75));
	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(b, i), 127);
}

TYPED_TEST(Test_Int8x16, And)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_3);
	typename TypeParam::ValueType c = TypeParam::And(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 1);
}

TYPED_TEST(Test_Int8x16, AndNot)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_3);
	typename TypeParam::ValueType c = TypeParam::AndNot(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 2);
}

TYPED_TEST(Test_Int8x16, Or)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_2);
	typename TypeParam::ValueType c = TypeParam::Or(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 3);
}

TYPED_TEST(Test_Int8x16, Xor)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_1);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8x16_3);
	typename TypeParam::ValueType c = TypeParam::Xor(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 2);
}

TYPED_TEST(Test_Int8x16, Min)
{
	typename TypeParam::ValueType a = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_64);
	typename TypeParam::ValueType b = TypeParam::LoadUnaligned(Test_Int8x16<TypeParam>::i8_16_75);
	typename TypeParam::ValueType c = TypeParam::Max(a, b);

	for (int i = 0; i < 16; ++i)
		EXPECT_EQ(TypeParam::GetLane(c, i), 75);
}
