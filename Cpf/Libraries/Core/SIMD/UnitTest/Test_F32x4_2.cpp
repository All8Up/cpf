//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_F32x4_2 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	CPF::SIMD::Reference::F32x4_2,
	CPF::SIMD::SSE4_1::F32x4_2
> F32x4_2_Types;

TYPED_TEST_CASE(TypedTest_F32x4_2, F32x4_2_Types);


TYPED_TEST(TypedTest_F32x4_2, Construction_BasicAccess_Near)
{
	using Type = TypeParam;

	// Test splat construction.
	Type a(1.0f);
	Type b(2.0f);

	EXPECT_TRUE(Near(a, { 1.0f, 1.0f }, 0.01f));
	EXPECT_TRUE(Near(b, { 2.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));

	// Test pair construction.
	Type aa = { 1.0f, 2.0f };
	EXPECT_TRUE(Near(aa, { 1.0f, 2.0f }, 0.01f));
}

TYPED_TEST(TypedTest_F32x4_2, Addition)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f };
	Type b(3.0f, 4.0f);

	Type c = a + b;
	EXPECT_TRUE(Near(c, { 4.0f, 6.0f }, 0.01f));
	EXPECT_TRUE(Valid(c));
}

TYPED_TEST(TypedTest_F32x4_2, Subtraction)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f };
	Type b(2.0f, 4.0f);

	Type d = b - a;
	EXPECT_TRUE(Near(d, { 1.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Valid(d));
}

TYPED_TEST(TypedTest_F32x4_2, Multiplication)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f };
	Type b(2.0f, 3.0f);

	Type e = a * b;
	EXPECT_TRUE(Near(e, { 2.0f, 6.0f }, 0.01f));
	EXPECT_TRUE(Valid(e));
}

TYPED_TEST(TypedTest_F32x4_2, Division)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f };
	Type b(2.0f, 3.0f);

	Type f = a / b;
	EXPECT_TRUE(Near(f, { 0.5f, 2.0f/3.0f }, 0.01f));
	EXPECT_TRUE(Valid(f));
}
