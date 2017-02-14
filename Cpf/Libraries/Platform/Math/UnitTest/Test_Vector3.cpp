//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Vector3.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Constants.hpp"
#include "Simd/Simd.hpp"


template <typename T>
class Test_Vector3 : public::testing::Test
{
public:
	static void Near(const T& a, const T& b)
	{
		EXPECT_NEAR(a.x, b.x, 0.01);
		EXPECT_NEAR(a.y, b.y, 0.01);
		EXPECT_NEAR(a.z, b.z, 0.01);
	}
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types <
	//	Cpf::Math::Vector3h,
	Cpf::Math::Vector3f,
	Cpf::Math::Vector3d,
	Cpf::Math::Vector3v<Cpf::Simd::Reference::Float32x4>
#if CPF_SIMD_AVX2
	, Cpf::Math::Vector3v<Cpf::Simd::Avx2::Float32x4>
#endif
#if CPF_SIMD_AVX
	, Cpf::Math::Vector3v<Cpf::Simd::Avx::Float32x4>
#endif
#if CPF_SIMD_SSE4a
	, Cpf::Math::Vector3v<Cpf::Simd::Sse4a::Float32x4>
#endif
#if CPF_SIMD_SSE4_2
	, Cpf::Math::Vector3v<Cpf::Simd::Sse4_2::Float32x4>
#endif
#if CPF_SIMD_SSE4_1
	, Cpf::Math::Vector3v<Cpf::Simd::Sse4_1::Float32x4>
#endif
#if CPF_SIMD_SSE3
	, Cpf::Math::Vector3v<Cpf::Simd::Sse3::Float32x4>
#endif
#if CPF_SIMD_SSE2
	, Cpf::Math::Vector3v<Cpf::Simd::Sse2::Float32x4>
#endif
#if CPF_SIMD_SSE1
	, Cpf::Math::Vector3v<Cpf::Simd::Sse1::Float32x4>
#endif
> Vector3_Types;
TYPED_TEST_CASE(Test_Vector3, Vector3_Types);


TYPED_TEST(Test_Vector3, CreateAndAccess)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3));
	EXPECT_EQ(ElementType(1), test.X());
	EXPECT_EQ(ElementType(2), test.Y());
	EXPECT_EQ(ElementType(3), test.Z());
}

TYPED_TEST(Test_Vector3, CopyConstruct)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3));
	TypeParam test2(test);

	EXPECT_EQ(test.X(), test2.X());
	EXPECT_EQ(test.Y(), test2.Y());
	EXPECT_EQ(test.Z(), test2.Z());
}

TYPED_TEST(Test_Vector3, ArrayAccess)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(ElementType(1), ElementType(2), ElementType(3));
	EXPECT_EQ(ElementType(1), test[0]);
	EXPECT_EQ(ElementType(2), test[1]);
	EXPECT_EQ(ElementType(3), test[2]);

	EXPECT_EQ(test.x, test[0]);
	EXPECT_EQ(test.y, test[1]);
	EXPECT_EQ(test.z, test[2]);
}

TYPED_TEST(Test_Vector3, ElementSetters)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test(TypeParam(0));
	test.X(ElementType(1));
	test.Y(ElementType(2));
	test.Z(ElementType(3));

	EXPECT_EQ(ElementType(1), test[0]);
	EXPECT_EQ(ElementType(2), test[1]);
	EXPECT_EQ(ElementType(3), test[2]);
}

TYPED_TEST(Test_Vector3, ExactCompare)
{
	TypeParam test0(1, 2, 3);
	TypeParam test1(1, 2, 3);
	TypeParam test2(TypeParam(0));

	EXPECT_TRUE(test0 == test1);
	EXPECT_FALSE(test0 == test2);
}

TYPED_TEST(Test_Vector3, ExactInequality)
{
	TypeParam test0(1, 2, 3);
	TypeParam test1(1, 2, 3);
	TypeParam test2(TypeParam(0));

	EXPECT_TRUE(test0 != test2);
	EXPECT_FALSE(test0 != test1);
}

TYPED_TEST(Test_Vector3, Negate)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3);
	TypeParam result(-test0);

	EXPECT_EQ(ElementType(-1), result[0]);
	EXPECT_EQ(ElementType(-2), result[1]);
	EXPECT_EQ(ElementType(-3), result[2]);
}

TYPED_TEST(Test_Vector3, Add)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3);
	TypeParam test1(1, 2, 3);
	TypeParam result = test0 + test1;

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
}

TYPED_TEST(Test_Vector3, Subtract)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3);
	TypeParam test1(1, 2, 3);
	TypeParam result = test0 - test1;

	EXPECT_EQ(ElementType(0), result.X());
	EXPECT_EQ(ElementType(0), result.Y());
	EXPECT_EQ(ElementType(0), result.Z());
}

TYPED_TEST(Test_Vector3, Multiply)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3);
	TypeParam result = test0 * ElementType(2);

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
}

TYPED_TEST(Test_Vector3, LeftMultiply)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam test0(1, 2, 3);
	TypeParam result = ElementType(2) * test0;

	EXPECT_EQ(ElementType(2), result.X());
	EXPECT_EQ(ElementType(4), result.Y());
	EXPECT_EQ(ElementType(6), result.Z());
}

TYPED_TEST(Test_Vector3, DotOperator)
{
	typedef typename TypeParam::ElementType ElementType;
	ElementType result;
	result = Dot(TypeParam::XAxis(), TypeParam::XAxis());
	EXPECT_EQ(result, 1);

	result = Dot(TypeParam::XAxis(), TypeParam::YAxis());
	EXPECT_EQ(result, 0);
}

TYPED_TEST(Test_Vector3, Divide)
{
	TypeParam test0(2, 4, 6);
	TypeParam result = test0 / 2;

	EXPECT_EQ(1, result.X());
	EXPECT_EQ(2, result.Y());
	EXPECT_EQ(3, result.Z());
}

TYPED_TEST(Test_Vector3, CrossOperator)
{
	EXPECT_TRUE((TypeParam::XAxis() ^ TypeParam::YAxis()) == TypeParam::ZAxis());
	EXPECT_TRUE((TypeParam::ZAxis() ^ TypeParam::XAxis()) == TypeParam::YAxis());
	EXPECT_TRUE((TypeParam::YAxis() ^ TypeParam::ZAxis()) == TypeParam::XAxis());
}

TYPED_TEST(Test_Vector3, AddAssign)
{
	TypeParam result = TypeParam(1, 2, 3);
	result += TypeParam(1, 2, 3);

	EXPECT_EQ(2, result.X());
	EXPECT_EQ(4, result.Y());
	EXPECT_EQ(6, result.Z());
}

TYPED_TEST(Test_Vector3, SubAssign)
{
	TypeParam result = TypeParam(1, 2, 3);
	result -= TypeParam(1, 2, 3);

	EXPECT_EQ(0, result.X());
	EXPECT_EQ(0, result.Y());
	EXPECT_EQ(0, result.Z());
}

TYPED_TEST(Test_Vector3, MulAssign)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam result = TypeParam(2, 4, 6);
	result *= ElementType(2);

	EXPECT_EQ(ElementType(4), result.X());
	EXPECT_EQ(ElementType(8), result.Y());
	EXPECT_EQ(ElementType(12), result.Z());
}

TYPED_TEST(Test_Vector3, DivAssign)
{
	typedef typename TypeParam::ElementType ElementType;
	TypeParam result = TypeParam(2, 4, 6);
	result /= ElementType(2);

	EXPECT_EQ(1, result.X());
	EXPECT_EQ(2, result.Y());
	EXPECT_EQ(3, result.Z());
}

TYPED_TEST(Test_Vector3, CrossAssign)
{
	{
		TypeParam res = TypeParam::XAxis();
		EXPECT_TRUE((res ^= TypeParam::YAxis()) == TypeParam::ZAxis());
	}
	{
		TypeParam res = TypeParam::ZAxis();
		EXPECT_TRUE((res ^= TypeParam::XAxis()) == TypeParam::YAxis());
	}
	{
		TypeParam res = TypeParam::YAxis();
		EXPECT_TRUE((res ^= TypeParam::ZAxis()) == TypeParam::XAxis());
	}
}

TYPED_TEST(Test_Vector3, Rotate)
{
	typedef typename TypeParam::ElementType ElementType;
	{
		TypeParam res = TypeParam::XAxis();
		res = Cpf::Math::Rotate(res, TypeParam::YAxis(), Cpf::Math::Constants<ElementType>::kHalfPI);
		EXPECT_NEAR(0, res.X(), 0.01);
		EXPECT_NEAR(0, res.Y(), 0.01);
		EXPECT_NEAR(-1, res.Z(), 0.01);
	}

	{
		TypeParam res = TypeParam::XAxis();
		res = Cpf::Math::Rotate(res, TypeParam::YAxis(), Cpf::Math::Constants<ElementType>::kPI);
		EXPECT_NEAR(-1, res.X(), 0.01);
		EXPECT_NEAR(0, res.Y(), 0.01);
		EXPECT_NEAR(0, res.Z(), 0.01);
	}

	{
		TypeParam res = TypeParam::YAxis();
		res = Cpf::Math::Rotate(res, TypeParam::XAxis(), Cpf::Math::Constants<ElementType>::kHalfPI);
		EXPECT_NEAR(0, res.X(), 0.01);
		EXPECT_NEAR(0, res.Y(), 0.01);
		EXPECT_NEAR(1, res.Z(), 0.01);
	}

	{
		TypeParam res = TypeParam::YAxis();
		res = Cpf::Math::Rotate(res, TypeParam::XAxis(), Cpf::Math::Constants<ElementType>::kPI);
		EXPECT_NEAR(0, res.X(), 0.01);
		EXPECT_NEAR(-1, res.Y(), 0.01);
		EXPECT_NEAR(0, res.Z(), 0.01);
	}

	{
		TypeParam res = TypeParam::ZAxis();
		res = Cpf::Math::Rotate(res, TypeParam::XAxis(), Cpf::Math::Constants<ElementType>::kHalfPI);
		EXPECT_NEAR(0, res.X(), 0.01);
		EXPECT_NEAR(-1, res.Y(), 0.01);
		EXPECT_NEAR(0, res.Z(), 0.01);
	}

	{
		TypeParam res = TypeParam::ZAxis();
		res = Cpf::Math::Rotate(res, TypeParam::XAxis(), Cpf::Math::Constants<ElementType>::kPI);
		EXPECT_NEAR(0, res.X(), 0.01);
		EXPECT_NEAR(0, res.Y(), 0.01);
		EXPECT_NEAR(-1, res.Z(), 0.01);
	}
}

TYPED_TEST(Test_Vector3, Magnitude)
{
	EXPECT_NEAR(Magnitude(TypeParam::XAxis()), 1, 0.01);
	EXPECT_NEAR(Magnitude(TypeParam::YAxis()), 1, 0.01);
	EXPECT_NEAR(Magnitude(TypeParam::ZAxis()), 1, 0.01);
}

TYPED_TEST(Test_Vector3, MagnitudeSquared)
{
	EXPECT_NEAR(MagnitudeSquared(TypeParam::XAxis()), 1, 0.01);
	EXPECT_NEAR(MagnitudeSquared(TypeParam::YAxis()), 1, 0.01);
	EXPECT_NEAR(MagnitudeSquared(TypeParam::ZAxis()), 1, 0.01);
}

TYPED_TEST(Test_Vector3, Normalize)
{
	TypeParam test = Normalize(TypeParam::XAxis());
	EXPECT_NEAR(test.X(), 1, 0.01);
	EXPECT_NEAR(test.Y(), 0, 0.01);
	EXPECT_NEAR(test.Z(), 0, 0.01);
}

TYPED_TEST(Test_Vector3, NormalizeTo)
{
	using ElementType = typename TypeParam::ElementType;
	TypeParam test = NormalizeTo(TypeParam::XAxis(), ElementType(2));
	EXPECT_NEAR(test.X(), 2, 0.01);
	EXPECT_NEAR(test.Y(), 0, 0.01);
	EXPECT_NEAR(test.Z(), 0, 0.01);
	EXPECT_NEAR(Magnitude(test), 2, 0.01);
	EXPECT_NEAR(MagnitudeSquared(test), 4, 0.01);
}

TYPED_TEST(Test_Vector3, Reflect)
{
	{
		TypeParam test = Reflect(TypeParam::XAxis(), TypeParam::YAxis());
		EXPECT_NEAR(test.X(), -1.0, 0.01);
		EXPECT_NEAR(test.Y(), 0.0, 0.01);
		EXPECT_NEAR(test.Z(), 0.0, 0.01);
	}
	{
		TypeParam test = Reflect(TypeParam::ZAxis(), TypeParam::YAxis());
		EXPECT_NEAR(test.X(), 0.0, 0.01);
		EXPECT_NEAR(test.Y(), 0.0, 0.01);
		EXPECT_NEAR(test.Z(), -1.0, 0.01);
	}
	{
		TypeParam test = Reflect(TypeParam::YAxis(), TypeParam::ZAxis());
		EXPECT_NEAR(test.X(), 0.0, 0.01);
		EXPECT_NEAR(test.Y(), -1.0, 0.01);
		EXPECT_NEAR(test.Z(), 0.0, 0.01);
	}
}

/* TODO
TYPED_TEST(Test_Vector3, Refract)
{
}
*/

TYPED_TEST(Test_Vector3, Distance)
{
	typename TypeParam::ElementType distance = Distance(TypeParam(1, 2, 3), TypeParam(2, 4, 6));
	EXPECT_NEAR(distance, 3.7416, 0.01);
}

TYPED_TEST(Test_Vector3, DistanceSquared)
{
	typename TypeParam::ElementType distance = DistanceSquared(TypeParam(1, 2, 3), TypeParam(2, 4, 6));
	EXPECT_NEAR(distance, 14, 0.01);
}

TYPED_TEST(Test_Vector3, ElementMultiply)
{
	TypeParam test = TypeParam(1, 2, 3) * TypeParam(1, 2, 3);
	EXPECT_NEAR(test.X(), 1, 0.001);
	EXPECT_NEAR(test.Y(), 4, 0.001);
	EXPECT_NEAR(test.Z(), 9, 0.001);
}
