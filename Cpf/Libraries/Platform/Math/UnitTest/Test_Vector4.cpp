//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Vector4.hpp"
#include "Math/Vector4v.hpp"
#include "Math/Constants.hpp"
#include "Simd/Simd.hpp"


template <typename T>
class Test_Vector4 : public::testing::Test
{
public:
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types <
	//	Cpf::Math::Vector4h,
	Cpf::Math::Vector4f
	, Cpf::Math::Vector4d
	, Cpf::Math::Vector4v<Cpf::Simd::Reference::Float32x4>
#if CPF_SIMD_AVX2
	, Cpf::Math::Vector4v<Cpf::Simd::Avx2::Float32x4>
#endif
#if CPF_SIMD_AVX
	, Cpf::Math::Vector4v<Cpf::Simd::Avx::Float32x4>
#endif
#if CPF_SIMD_SSE4a
	, Cpf::Math::Vector4v<Cpf::Simd::Sse4a::Float32x4>
#endif
#if CPF_SIMD_SSE4_2
	, Cpf::Math::Vector4v<Cpf::Simd::Sse4_2::Float32x4>
#endif
#if CPF_SIMD_SSE4_1
	, Cpf::Math::Vector4v<Cpf::Simd::Sse4_1::Float32x4>
#endif
#if CPF_SIMD_SSE3
	, Cpf::Math::Vector4v<Cpf::Simd::Sse3::Float32x4>
#endif
#if CPF_SIMD_SSE2
	, Cpf::Math::Vector4v<Cpf::Simd::Sse2::Float32x4>
#endif
#if CPF_SIMD_SSE1
	, Cpf::Math::Vector4v<Cpf::Simd::Sse1::Float32x4>
#endif
> Vector4_Types;
TYPED_TEST_CASE(Test_Vector4, Vector4_Types);




TYPED_TEST(Test_Vector4, CreateAndAccess)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3), ElementType(4));
	EXPECT_EQ(ElementType(1), test.X());
	EXPECT_EQ(ElementType(2), test.Y());
	EXPECT_EQ(ElementType(3), test.Z());
	EXPECT_EQ(ElementType(4), test.W());
}

TYPED_TEST(Test_Vector4, CopyConstruct)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3), ElementType(4));
	TypeParam test2(test);

	EXPECT_EQ(test.X(), test2.X());
	EXPECT_EQ(test.Y(), test2.Y());
	EXPECT_EQ(test.Z(), test2.Z());
	EXPECT_EQ(test.W(), test2.W());
}

TYPED_TEST(Test_Vector4, ArrayAccess)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3), ElementType(4));
	EXPECT_EQ(ElementType(1), test[0]);
	EXPECT_EQ(ElementType(2), test[1]);
	EXPECT_EQ(ElementType(3), test[2]);
	EXPECT_EQ(ElementType(4), test[3]);
}

TYPED_TEST(Test_Vector4, ElementSetters)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(TypeParam(0));
	test.X(ElementType(1));
	test.Y(ElementType(2));
	test.Z(ElementType(3));
	test.W(ElementType(4));

	EXPECT_EQ(ElementType(1), test[0]);
	EXPECT_EQ(ElementType(2), test[1]);
	EXPECT_EQ(ElementType(3), test[2]);
	EXPECT_EQ(ElementType(4), test[3]);
}

TYPED_TEST(Test_Vector4, ExactCompare)
{
	TypeParam test0(1, 2, 3, 4);
	TypeParam test1(1, 2, 3, 4);
	TypeParam test2(TypeParam(0));

	EXPECT_TRUE(test0 == test1);
	EXPECT_FALSE(test0 == test2);
}

TYPED_TEST(Test_Vector4, ExactInequality)
{
	TypeParam test0(1, 2, 3, 4);
	TypeParam test1(1, 2, 3, 4);
	TypeParam test2(TypeParam(0));

	EXPECT_TRUE(test0 != test2);
	EXPECT_FALSE(test0 != test1);
}

TYPED_TEST(Test_Vector4, Negate)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3, 4);
	TypeParam result(-test0);

	EXPECT_EQ(ElementType(-1), result[0]);
	EXPECT_EQ(ElementType(-2), result[1]);
	EXPECT_EQ(ElementType(-3), result[2]);
	EXPECT_EQ(ElementType(-4), result[3]);
}

TYPED_TEST(Test_Vector4, Add)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3, 4);
	TypeParam test1(1, 2, 3, 4);
	TypeParam result = test0 + test1;

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
	EXPECT_EQ(ElementType(8), result.W());
}

TYPED_TEST(Test_Vector4, Subtract)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3, 4);
	TypeParam test1(1, 2, 3, 4);
	TypeParam result = test0 - test1;

	EXPECT_EQ(ElementType(0), result.X());
	EXPECT_EQ(ElementType(0), result.Y());
	EXPECT_EQ(ElementType(0), result.Z());
	EXPECT_EQ(ElementType(0), result.W());
}

TYPED_TEST(Test_Vector4, Multiply)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3, 4);
	TypeParam result = test0 * ElementType(2);

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
	EXPECT_EQ(ElementType(8), result.W());
}

TYPED_TEST(Test_Vector4, LeftMultiply)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3, 4);
	TypeParam result = ElementType(2) * test0;

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
	EXPECT_EQ(ElementType(8), result.W());
}

TYPED_TEST(Test_Vector4, DotOperator)
{
	typedef typename TypeParam::ElementType ElementType;
	ElementType result;
	result = Dot(TypeParam::XAxis(), TypeParam::XAxis());
	EXPECT_EQ(result, 1);

	result = Dot(TypeParam::XAxis(), TypeParam::YAxis());
	EXPECT_EQ(result, 0);
}

TYPED_TEST(Test_Vector4, Divide)
{
	TypeParam test0(2, 4, 6, 8);
	TypeParam result = test0 / 2;

	EXPECT_EQ(1, result.X());
	EXPECT_EQ(2, result.Y());
	EXPECT_EQ(3, result.Z());
	EXPECT_EQ(4, result.W());
}

TYPED_TEST(Test_Vector4, AddAssign)
{
	TypeParam result = TypeParam(1, 2, 3, 4);
	result += TypeParam(1, 2, 3, 4);

	EXPECT_EQ(2, result.X());
	EXPECT_EQ(4, result.Y());
	EXPECT_EQ(6, result.Z());
	EXPECT_EQ(8, result.W());
}

TYPED_TEST(Test_Vector4, SubAssign)
{
	TypeParam result = TypeParam(1, 2, 3, 4);
	result -= TypeParam(1, 2, 3, 4);

	EXPECT_EQ(0, result.X());
	EXPECT_EQ(0, result.Y());
	EXPECT_EQ(0, result.Z());
	EXPECT_EQ(0, result.W());
}

TYPED_TEST(Test_Vector4, MulAssign)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam result = TypeParam(2, 4, 6, 8);
	result *= ElementType(2);

	EXPECT_EQ(ElementType(4), result.X());
	EXPECT_EQ(ElementType(8), result.Y());
	EXPECT_EQ(ElementType(12), result.Z());
	EXPECT_EQ(ElementType(16), result.W());
}

TYPED_TEST(Test_Vector4, DivAssign)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam result = TypeParam(2, 4, 6, 8);
	result /= ElementType(2);

	EXPECT_EQ(1, result.X());
	EXPECT_EQ(2, result.Y());
	EXPECT_EQ(3, result.Z());
	EXPECT_EQ(4, result.W());
}

TYPED_TEST(Test_Vector4, Magnitude)
{
	EXPECT_NEAR(Magnitude(TypeParam::XAxis()), 1, 0.01);
	EXPECT_NEAR(Magnitude(TypeParam::YAxis()), 1, 0.01);
	EXPECT_NEAR(Magnitude(TypeParam::ZAxis()), 1, 0.01);
}

TYPED_TEST(Test_Vector4, MagnitudeSquared)
{
	EXPECT_NEAR(MagnitudeSquared(TypeParam::XAxis()), 1, 0.01);
	EXPECT_NEAR(MagnitudeSquared(TypeParam::YAxis()), 1, 0.01);
	EXPECT_NEAR(MagnitudeSquared(TypeParam::ZAxis()), 1, 0.01);
}

TYPED_TEST(Test_Vector4, Normalize)
{
	TypeParam test = Normalize(TypeParam::XAxis());
	EXPECT_NEAR(test.X(), 1, 0.01);
	EXPECT_NEAR(test.Y(), 0, 0.01);
	EXPECT_NEAR(test.Z(), 0, 0.01);
	EXPECT_NEAR(test.W(), 0, 0.01);
}

TYPED_TEST(Test_Vector4, NormalizeTo)
{
	using ElementType = typename TypeParam::ElementType;
	TypeParam test = NormalizeTo(TypeParam::XAxis(), ElementType(2));
	EXPECT_NEAR(test.X(), 2, 0.01);
	EXPECT_NEAR(test.Y(), 0, 0.01);
	EXPECT_NEAR(test.Z(), 0, 0.01);
	EXPECT_NEAR(test.W(), 0, 0.01);
	EXPECT_NEAR(Magnitude(test), 2, 0.01);
	EXPECT_NEAR(MagnitudeSquared(test), 4, 0.01);
}

TYPED_TEST(Test_Vector4, Reflect)
{
	{
		TypeParam test = Reflect(TypeParam::XAxis(), TypeParam::YAxis());
		EXPECT_NEAR(test.X(), -1.0, 0.01);
		EXPECT_NEAR(test.Y(), 0.0, 0.01);
		EXPECT_NEAR(test.Z(), 0.0, 0.01);
		EXPECT_NEAR(test.W(), 0.0, 0.01);
	}
	{
		TypeParam test = Reflect(TypeParam::ZAxis(), TypeParam::YAxis());
		EXPECT_NEAR(test.X(), 0.0, 0.01);
		EXPECT_NEAR(test.Y(), 0.0, 0.01);
		EXPECT_NEAR(test.Z(), -1.0, 0.01);
		EXPECT_NEAR(test.W(), 0.0, 0.01);
	}
	{
		TypeParam test = Reflect(TypeParam::YAxis(), TypeParam::ZAxis());
		EXPECT_NEAR(test.X(), 0.0, 0.01);
		EXPECT_NEAR(test.Y(), -1.0, 0.01);
		EXPECT_NEAR(test.Z(), 0.0, 0.01);
		EXPECT_NEAR(test.W(), 0.0, 0.01);
	}
}

/* TODO
TYPED_TEST(Test_Vector4, Refract)
{
}
*/

TYPED_TEST(Test_Vector4, Distance)
{
	typename TypeParam::ElementType distance = Distance(TypeParam(1, 2, 3, 4), TypeParam(2, 4, 6, 8));
	EXPECT_NEAR(distance, 5.4772, 0.01);
}

TYPED_TEST(Test_Vector4, DistanceSquared)
{
	typename TypeParam::ElementType distance = DistanceSquared(TypeParam(1, 2, 3, 4), TypeParam(2, 4, 6, 8));
	EXPECT_NEAR(distance, 30, 0.01);
}
