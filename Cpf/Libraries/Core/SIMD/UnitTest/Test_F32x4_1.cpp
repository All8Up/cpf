//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SIMD.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_F32x4_1 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::SIMD::Reference::F32x4_1,
	Cpf::SIMD::SSE4_1::F32x4_1
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_F32x4_1, F32x4_1_Types);


TYPED_TEST(TypedTest_F32x4_1, Construction_BasicAccess_Near)
{
	using Type = typename TypeParam;

	Type a(1.0f);
	Type b(2.0f);

	EXPECT_NEAR(a, 1.0f, 0.01f);
	EXPECT_TRUE(Near(a, 1.0f, 0.01f));
	EXPECT_NEAR(b, 2.0f, 0.01f);
	EXPECT_TRUE(Near(b, 2.0f, 0.01f));

	EXPECT_FALSE(Near(a, 2.0f, 0.01f));
	EXPECT_FALSE(Near(b, 1.0f, 0.01f));

	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));
}

TYPED_TEST(TypedTest_F32x4_1, Addition)
{
	using Type = typename TypeParam;
	Type a(1.0f);
	Type b(2.0f);

	Type c = a + b;
	EXPECT_NEAR(c, 3.0f, 0.01f);
	EXPECT_TRUE(Valid(c));
}

TYPED_TEST(TypedTest_F32x4_1, Subtraction)
{
	using Type = typename TypeParam;
	Type a(1.0f);
	Type b(2.0f);

	Type d = b - a;
	EXPECT_NEAR(d, 1.0f, 0.01f);
	EXPECT_TRUE(Valid(d));
}

TYPED_TEST(TypedTest_F32x4_1, Multiplication)
{
	using Type = typename TypeParam;
	Type a(1.0f);
	Type b(2.0f);

	Type e = a * b;
	EXPECT_NEAR(e, 2.0f, 0.01f);
	EXPECT_TRUE(Valid(e));
}

TYPED_TEST(TypedTest_F32x4_1, Division)
{
	using Type = typename TypeParam;
	Type a(1.0f);
	Type b(2.0f);

	Type f = a / b;
	EXPECT_NEAR(f, 0.5f, 0.01f);
	EXPECT_TRUE(Valid(f));
}
