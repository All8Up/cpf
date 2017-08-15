//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_F32x4_4 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::SIMD::Reference::F32x4_4,
	Cpf::SIMD::SSE4_1::F32x4_4
> F32x4_4_Types;

TYPED_TEST_CASE(TypedTest_F32x4_4, F32x4_4_Types);


TYPED_TEST(TypedTest_F32x4_4, Construction_BasicAccess_Near)
{
	using Type = TypeParam;

	// Test splat construction.
	Type a(1.0f);
	Type b(2.0f);

	EXPECT_TRUE(Near(a, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.01f));
	EXPECT_TRUE(Near(b, { 2.0f, 2.0f, 2.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));

	// Test pair construction.
	Type aa = { 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_TRUE(Near(aa, { 1.0f, 2.0f, 3.0f, 4.0f }, 0.01f));
}

TYPED_TEST(TypedTest_F32x4_4, Addition)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f, 3.0f, 4.0f };
	Type b(3.0f, 4.0f, 5.0f, 6.0f);

	Type c = a + b;
	EXPECT_TRUE(Near(c, { 4.0f, 6.0f, 8.0f, 10.0f }, 0.01f));
	EXPECT_TRUE(Valid(c));
}

TYPED_TEST(TypedTest_F32x4_4, Subtraction)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f, 3.0f, 4.0f };
	Type b(2.0f, 4.0f, 5.0f, 6.0f);

	Type d = b - a;
	EXPECT_TRUE(Near(d, { 1.0f, 2.0f, 2.0f, 2.0f }, 0.01f));
	EXPECT_TRUE(Valid(d));
}

TYPED_TEST(TypedTest_F32x4_4, Multiplication)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f, 3.0f, 4.0f };
	Type b(2.0f, 3.0f, 4.0f, 5.0f);

	Type e = a * b;
	EXPECT_TRUE(Near(e, { 2.0f, 6.0f, 12.0f, 20.0f }, 0.01f));
	EXPECT_TRUE(Valid(e));
}

TYPED_TEST(TypedTest_F32x4_4, Division)
{
	using Type = TypeParam;
	Type a = { 1.0f, 2.0f, 3.0f, 4.0f };
	Type b(2.0f, 3.0f, 4.0f, 5.0f);

	Type f = a / b;
	EXPECT_TRUE(Near(f, { 0.5f, 2.0f / 3.0f, 3.0f / 4.0f, 4.0f / 5.0f }, 0.01f));
	EXPECT_TRUE(Valid(f));
}
