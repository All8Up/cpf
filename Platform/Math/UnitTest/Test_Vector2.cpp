//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

template <typename T>
class Test_Vector2 : public::testing::Test
{
public:
};

//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types <
//	Cpf::Math::Vector2h,
	Cpf::Math::Vector2f
> Vector2_Types;
TYPED_TEST_CASE(Test_Vector2, Vector2_Types);

//////////////////////////////////////////////////////////////////////////
TYPED_TEST(Test_Vector2, CreateAndAccess)
{
	using Type = TypeParam;
	using ElementType = typename TypeParam::ElementType;
	Type a(ElementType(1), ElementType(2));

	EXPECT_EQ(a.x, a.data[0]);
	EXPECT_EQ(a.y, a.data[1]);
}

TYPED_TEST(Test_Vector2, Swizzle2)
{
	using Type = TypeParam;
	using ElementType = typename TypeParam::ElementType;
	Type a(ElementType(1), ElementType(2));

	EXPECT_EQ(1, Type(a.xx)[0]);
	EXPECT_EQ(1, Type(a.xx)[1]);

	EXPECT_EQ(2, Type(a.yy)[0]);
	EXPECT_EQ(2, Type(a.yy)[1]);

	EXPECT_EQ(2, Type(a.yx)[0]);
	EXPECT_EQ(1, Type(a.yx)[1]);
}

TYPED_TEST(Test_Vector2, Swizzle3)
{
	using Type = TypeParam;
	using ElementType = typename TypeParam::ElementType;
	Type a(ElementType(1), ElementType(2));

	EXPECT_EQ(1, Cpf::Math::Vector3<ElementType>(a.xxx)[0]);
	EXPECT_EQ(1, Cpf::Math::Vector3<ElementType>(a.xxy)[1]);
	EXPECT_EQ(2, Cpf::Math::Vector3<ElementType>(a.xyy)[2]);

	EXPECT_EQ(2, Cpf::Math::Vector3<ElementType>(a.yyy)[0]);
	EXPECT_EQ(2, Cpf::Math::Vector3<ElementType>(a.yyx)[1]);
	EXPECT_EQ(1, Cpf::Math::Vector3<ElementType>(a.yxx)[2]);

	EXPECT_EQ(2, Cpf::Math::Vector3<ElementType>(a.yxy)[0]);
	EXPECT_EQ(1, Cpf::Math::Vector3<ElementType>(a.yxy)[1]);
}

TYPED_TEST(Test_Vector2, Swizzle4)
{
	using Type = TypeParam;
	using ElementType = typename TypeParam::ElementType;
	Type a(ElementType(1), ElementType(2));

	EXPECT_EQ(1, Cpf::Math::Vector4<ElementType>(a.xxxx)[0]);
	EXPECT_EQ(1, Cpf::Math::Vector4<ElementType>(a.xxyy)[1]);
	EXPECT_EQ(2, Cpf::Math::Vector4<ElementType>(a.xyyy)[2]);
	EXPECT_EQ(2, Cpf::Math::Vector4<ElementType>(a.xyyy)[3]);

	EXPECT_EQ(1, Cpf::Math::Vector4<ElementType>(a.xyyy)[0]);
	EXPECT_EQ(2, Cpf::Math::Vector4<ElementType>(a.xyyx)[1]);
	EXPECT_EQ(1, Cpf::Math::Vector4<ElementType>(a.xyxx)[2]);

	EXPECT_EQ(1, Cpf::Math::Vector4<ElementType>(a.xyxy)[0]);
	EXPECT_EQ(2, Cpf::Math::Vector4<ElementType>(a.xyxy)[1]);
}

TYPED_TEST(Test_Vector2, SwizzleAssign)
{
	using Type = TypeParam;
	using ElementType = typename TypeParam::ElementType;

	Type a(ElementType(1), ElementType(2));
	a.yx = Type(5, 4);

	EXPECT_EQ(4, a[0]);
	EXPECT_EQ(5, a[1]);
}
