#include <gtest/gtest.h>
#include "CPF/SIMD.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_FXXx4_4 : public::testing::Test
{
public:
};

typedef ::testing::Types <
	CPF::SIMD::Reference::F32x4_4,
	CPF::SIMD::Reference::F64x4_4,
	CPF::SIMD::SSE4_1::F32x4_4,
	CPF::SIMD::SSE4_1::F64x4_4
> F32x4_4_Types;

TYPED_TEST_CASE(TypedTest_FXXx4_4, F32x4_4_Types);


TYPED_TEST(TypedTest_FXXx4_4, Construction_BasicAccess_Near)
{
	using Type = TypeParam;
	using Lane = typename Type::LaneType;

	// Test splat construction.
	Type a(Lane(1.0));
	Type b(Lane(2.0));

	EXPECT_TRUE(Near(a, { Lane(1.0), Lane(1.0), Lane(1.0), Lane(1.0) }, Lane(0.01)));
	EXPECT_TRUE(Near(b, { Lane(2.0), Lane(2.0), Lane(2.0), Lane(2.0) }, Lane(0.01)));
	EXPECT_TRUE(Valid(a));
	EXPECT_TRUE(Valid(b));

	// Test construction combinations.
	Type aa = { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) };
	EXPECT_TRUE(Near(aa, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	// Identity, just a validation.
	Type dd = { typename Type::Lanes_4{ Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) } };
	EXPECT_TRUE(Near(dd, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	// Variations with 2 lane items.
	Type bb = { {Lane(1.0), Lane(2.0)}, Lane(3.0), Lane(4.0) };
	EXPECT_TRUE(Near(bb, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	Type ee = { Lane(1.0), typename Type::Lanes_2{Lane(2.0), Lane(3.0)}, Lane(4.0) };
	EXPECT_TRUE(Near(ee, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	Type ff = { Lane(1.0), Lane(2.0), typename Type::Lanes_2{ Lane(3.0), Lane(4.0) } };
	EXPECT_TRUE(Near(ff, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	// Variations with 3 lane items.
	Type cc = { typename Type::Lanes_3{ Lane(1.0), Lane(2.0), Lane(3.0) }, Lane(4.0) };
	EXPECT_TRUE(Near(cc, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));

	Type gg = { Lane(1.0), typename Type::Lanes_3{ Lane(2.0), Lane(3.0), Lane(4.0) } };
	EXPECT_TRUE(Near(gg, { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) }, Lane(0.01)));
}

TYPED_TEST(TypedTest_FXXx4_4, Addition)
{
	using Type = TypeParam;
	using Lane = typename Type::LaneType;

	Type a = { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) };
	Type b(Lane(3.0), Lane(4.0), Lane(5.0), Lane(6.0));

	Type c = a + b;
	EXPECT_TRUE(Near(c, { Lane(4.0), Lane(6.0), Lane(8.0), Lane(10.0) }, Lane(0.01)));
	EXPECT_TRUE(Valid(c));
}

TYPED_TEST(TypedTest_FXXx4_4, Subtraction)
{
	using Type = TypeParam;
	using Lane = typename Type::LaneType;

	Type a = { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) };
	Type b(Lane(2.0), Lane(4.0), Lane(5.0), Lane(6.0));

	Type d = b - a;
	EXPECT_TRUE(Near(d, { Lane(1.0), Lane(2.0), Lane(2.0), Lane(2.0) }, Lane(0.01)));
	EXPECT_TRUE(Valid(d));
}

TYPED_TEST(TypedTest_FXXx4_4, Multiplication)
{
	using Type = TypeParam;
	using Lane = typename Type::LaneType;

	Type a = { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) };
	Type b(Lane(2.0), Lane(4.0), Lane(5.0), Lane(6.0));

	Type e = a * b;
	EXPECT_TRUE(Near(e, { Lane(2.0), Lane(8.0), Lane(15.0), Lane(24.0) }, Lane(0.01)));
	EXPECT_TRUE(Valid(e));
}

TYPED_TEST(TypedTest_FXXx4_4, Division)
{
	using Type = TypeParam;
	using Lane = typename Type::LaneType;

	Type a = { Lane(1.0), Lane(2.0), Lane(3.0), Lane(4.0) };
	Type b(Lane(2.0), Lane(4.0), Lane(5.0), Lane(6.0));

	Type f = a / b;
	EXPECT_TRUE(Near(f, { Lane(0.5), Lane(0.5), Lane(3.0) / Lane(5.0), Lane(4.0) / Lane(6.0) }, Lane(0.01)));
	EXPECT_TRUE(Valid(f));
}
