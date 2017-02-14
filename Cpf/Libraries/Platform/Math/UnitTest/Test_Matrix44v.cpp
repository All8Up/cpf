//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Matrix44v.hpp"


using namespace Cpf::Math;


template <typename TYPE>
class Test_Matrix44v : public::testing::Test
{
public:
	Test_Matrix44v()
		: series(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16)
	{
	}

	bool ValidateSeries(const TYPE& matrix)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				::testing::internal::FloatingPoint<typename TYPE::ElementType> lhs( matrix[i][j] );
				if (!lhs.AlmostEquals(::testing::internal::FloatingPoint<typename TYPE::ElementType>(typename TYPE::ElementType((i * 4 + j) + 1) )))
					return false;
			}
		return true;
	}

	template<typename RHS>
	bool Compare(const TYPE& lhs, const RHS& rhs)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				::testing::internal::FloatingPoint<typename TYPE::ElementType> _lhs(lhs[i][j]);
				::testing::internal::FloatingPoint<typename TYPE::ElementType> _rhs(rhs[i][j]);
				if (!_lhs.AlmostEquals(_rhs))
					return false;
			}
		return true;
	}

	TYPE series;
};


//////////////////////////////////////////////////////////////////////////
typedef ::testing::Types <
	Cpf::Math::Matrix44fv
#if CPF_SIMD_AVX2
#endif
#if CPF_SIMD_AVX
#endif
#if CPF_SIMD_SSE4a
#endif
#if CPF_SIMD_SSE4_2
#endif
#if CPF_SIMD_SSE4_1
#endif
#if CPF_SIMD_SSE3
#endif
#if CPF_SIMD_SSE2
#endif
#if CPF_SIMD_SSE1
#endif
> Matrix44_Types;
TYPED_TEST_CASE(Test_Matrix44v, Matrix44_Types);


#if 0

TYPED_TEST(Test_Matrix44v, ValidateRowColumnAccessor)
{
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(0, 0), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(0, 1), 2, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(0, 2), 3, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(0, 3), 4, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(1, 0), 5, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(1, 1), 6, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(1, 2), 7, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(1, 3), 8, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(2, 0), 9, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(2, 1), 10, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(2, 2), 11, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(2, 3), 12, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(3, 0), 13, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(3, 1), 14, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(3, 2), 15, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series(3, 3), 16, typename TypeParam::ElementType(0.0001));
}

TYPED_TEST(Test_Matrix44v, ValidateRowIndexing)
{
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(Test_Matrix44v<TypeParam>::series));
}

TYPED_TEST(Test_Matrix44v, ValidateMemoryLayoutCreate)
{
	typename TypeParam::ElementType inputs[] =
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	};

	{
		// Constructor.
		TypeParam seriesFromMemory(inputs);
		EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(seriesFromMemory));
	}
	{
		// Assignment.
		TypeParam seriesFromMemory;
		seriesFromMemory = inputs;

		EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(seriesFromMemory));
	}
	{
		// Set method.
		TypeParam seriesFromMemory;
		seriesFromMemory.Set(inputs);
		EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(seriesFromMemory));
	}
}

TYPED_TEST(Test_Matrix44v, CopyConstructor)
{
	TypeParam test(Test_Matrix44v<TypeParam>::series);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, RowConstructor)
{
	using RowType = typename TypeParam::RowType;
	TypeParam test(
		RowType(1, 2, 3, 4),
		RowType(5, 6, 7, 8),
		RowType(9, 10, 11, 12),
		RowType(13, 14, 15, 16)
		);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));

	Matrix44fv testf(
		Vector4fv(1, 2, 3, 4),
		Vector4fv(5, 6, 7, 8),
		Vector4fv(9, 10, 11, 12),
		Vector4fv(13, 14, 15, 16)
	);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test, testf));
}

TYPED_TEST(Test_Matrix44v, RowMethod)
{
	TypeParam test(Test_Matrix44v<TypeParam>::series[0], Test_Matrix44v<TypeParam>::series[1], Test_Matrix44v<TypeParam>::series[2], Test_Matrix44v<TypeParam>::series[3]);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, ColumnMethod)
{
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(0)[0], 1, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(0)[1], 5, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(0)[2], 9, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(0)[3], 13, 0.001);

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(1)[0], 2, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(1)[1], 6, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(1)[2], 10, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(1)[3], 14, 0.001);

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(2)[0], 3, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(2)[1], 7, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(2)[2], 11, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(2)[3], 15, 0.001);

	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(3)[0], 4, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(3)[1], 8, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(3)[2], 12, 0.001);
	EXPECT_NEAR(Test_Matrix44v<TypeParam>::series.Column(3)[3], 16, 0.001);
}

TYPED_TEST(Test_Matrix44v, SetFromMatrixMethod)
{
	TypeParam test;
	test.Set(Test_Matrix44v<TypeParam>::series);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, SetFromValuesMethod)
{
	TypeParam test;
	test.Set(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, AssignmentMatrixOperator)
{
	TypeParam test;
	test = Test_Matrix44v<TypeParam>::series;
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, ScalarMultiplyDivide)
{
	{
		TypeParam test = Test_Matrix44v<TypeParam>::series * 2;
		EXPECT_NEAR(test(0, 0), 2, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 1), 4, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 2), 6, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 3), 8, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(1, 0), 10, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 1), 12, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 2), 14, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 3), 16, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(2, 0), 18, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 1), 20, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 2), 22, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 3), 24, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(3, 0), 26, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 1), 28, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 2), 30, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 3), 32, typename TypeParam::ElementType(0.0001));

		test /= 2;
		EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
	}
	{
		TypeParam test = 2 * Test_Matrix44v<TypeParam>::series;
		EXPECT_NEAR(test(0, 0), 2, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 1), 4, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 2), 6, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(0, 3), 8, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(1, 0), 10, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 1), 12, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 2), 14, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(1, 3), 16, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(2, 0), 18, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 1), 20, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 2), 22, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(2, 3), 24, typename TypeParam::ElementType(0.0001));

		EXPECT_NEAR(test(3, 0), 26, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 1), 28, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 2), 30, typename TypeParam::ElementType(0.0001));
		EXPECT_NEAR(test(3, 3), 32, typename TypeParam::ElementType(0.0001));
	}
}

TYPED_TEST(Test_Matrix44v, ScalarDivide)
{
	TypeParam test = Test_Matrix44v<TypeParam>::series / 0.5;
	EXPECT_NEAR(test(0, 0), 2, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 1), 4, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 2), 6, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 3), 8, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(1, 0), 10, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 1), 12, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 2), 14, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 3), 16, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(2, 0), 18, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 1), 20, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 2), 22, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 3), 24, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(3, 0), 26, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 1), 28, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 2), 30, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 3), 32, typename TypeParam::ElementType(0.0001));

	test *= 0.5;
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, Multiplication)
{
	TypeParam test = Test_Matrix44v<TypeParam>::series * TypeParam::Identity();
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));

	test *= TypeParam::Identity();
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::ValidateSeries(test));
}

TYPED_TEST(Test_Matrix44v, Transpose)
{
	TypeParam test = Transpose(Test_Matrix44v<TypeParam>::series);
	EXPECT_NEAR(test(0, 0), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 1), 5, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 2), 9, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 3), 13, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(1, 0), 2, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 1), 6, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 2), 10, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 3), 14, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(2, 0), 3, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 1), 7, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 2), 11, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 3), 15, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(3, 0), 4, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 1), 8, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 2), 12, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 3), 16, typename TypeParam::ElementType(0.0001));
}

TYPED_TEST(Test_Matrix44v, RotateX)
{
	TypeParam test = TypeParam::RotateX(Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	EXPECT_NEAR(test(0, 0), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(1, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 2), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(2, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 1), -1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(3, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 3), 1, typename TypeParam::ElementType(0.0001));

	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test, Matrix44fv::RotateX(Constants<typename TypeParam::ElementType>::DegToRad() * 90)));
}

TYPED_TEST(Test_Matrix44v, RotateY)
{
	TypeParam test = TypeParam::RotateY(Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	EXPECT_NEAR(test(0, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 2), -1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(1, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 1), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(2, 0), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(3, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 3), 1, typename TypeParam::ElementType(0.0001));

	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test, Matrix44fv::RotateY(Constants<typename TypeParam::ElementType>::DegToRad() * 90)));
}

TYPED_TEST(Test_Matrix44v, RotateZ)
{
	TypeParam test = TypeParam::RotateZ(Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	EXPECT_NEAR(test(0, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 1), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(0, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(1, 0), -1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(1, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(2, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 2), 1, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(2, 3), 0, typename TypeParam::ElementType(0.0001));

	EXPECT_NEAR(test(3, 0), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 1), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 2), 0, typename TypeParam::ElementType(0.0001));
	EXPECT_NEAR(test(3, 3), 1, typename TypeParam::ElementType(0.0001));

	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test, Matrix44fv::RotateZ(Constants<typename TypeParam::ElementType>::DegToRad() * 90)));
}

TYPED_TEST(Test_Matrix44v, RotateAxis)
{
	TypeParam test0x = TypeParam::RotateX(Constants<typename TypeParam::ElementType>::DegToRad() * 90);
	TypeParam test1x = TypeParam::Rotate(Vector3v<typename TypeParam::SimdType>::XAxis(), Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	TypeParam test0y = TypeParam::RotateY(Constants<typename TypeParam::ElementType>::DegToRad() * 90);
	TypeParam test1y = TypeParam::Rotate(Vector3v<typename TypeParam::SimdType>::YAxis(), Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	TypeParam test0z = TypeParam::RotateZ(Constants<typename TypeParam::ElementType>::DegToRad() * 90);
	TypeParam test1z = TypeParam::Rotate(Vector3v<typename TypeParam::SimdType>::ZAxis(), Constants<typename TypeParam::ElementType>::DegToRad() * 90);

	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test0x, test1x));
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test0y, test1y));
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(test0z, test1z));
}

TYPED_TEST(Test_Matrix44v, InvertIdentity)
{
	TypeParam ident = TypeParam::Identity();
	TypeParam iIdent = Invert(ident);
	EXPECT_TRUE(Test_Matrix44v<TypeParam>::Compare(ident, iIdent));
}

TYPED_TEST(Test_Matrix44v, InvertRotation)
{
	using Vector3 = Vector3v<typename TypeParam::SimdType>;
	using Vector4 = Vector4v<typename TypeParam::SimdType>;
	using ElementType = typename TypeParam::ElementType;

	// Test against rotational matrices.
	Vector3v<typename TypeParam::SimdType> tvec(1, 1, 1);
	for (int i = 0; i < 360; i += 10)
	{
		for (int j = 0; j < 360; j += 10)
		{
			for (int k = 0; k < 360; k += 10)
			{
				TypeParam testX = TypeParam::RotateX(Constants<ElementType>::DegToRad() * i);
				TypeParam testY = TypeParam::RotateY(Constants<ElementType>::DegToRad() * j);
				TypeParam testZ = TypeParam::RotateZ(Constants<ElementType>::DegToRad() * k);
				TypeParam test = testX * testY * testZ;
				Vector3 x((Vector4::XAxis() * test).xyz);
				Vector3 y((Vector4::YAxis() * test).xyz);
				Vector3 z((Vector4::ZAxis() * test).xyz);

				TypeParam iTest = Invert(test);
				Vector3 ix((Vector4(x, 1) * iTest).xyz);
				Vector3 iy((Vector4(y, 1) * iTest).xyz);
				Vector3 iz((Vector4(z, 1) * iTest).xyz);

				EXPECT_NEAR(ix.X(), 1, 0.0001);
				EXPECT_NEAR(iy.Y(), 1, 0.0001);
				EXPECT_NEAR(iz.Z(), 1, 0.0001);

				EXPECT_NEAR(iTest[3][3], 1, 0.0001);

				Vector3 v = (Vector4(tvec, 1) * (test * iTest)).xyz;
				EXPECT_NEAR(v.X(), 1, 0.0001);
				EXPECT_NEAR(v.Y(), 1, 0.0001);
				EXPECT_NEAR(v.Z(), 1, 0.0001);
			}
		}
	}
}


TYPED_TEST(Test_Matrix44v, InvertScale)
{
	using ElementType = typename TypeParam::ElementType;
	using Vector3 = Vector3v<typename TypeParam::SimdType>;

	// Test against scale matrices.
	for (int i = 1; i < 10; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			for (int k = 1; k < 10; ++k)
			{
				TypeParam scale = TypeParam::Scale(ElementType(i), ElementType(j), ElementType(k));
				TypeParam iscale = Invert(scale);

				Vector3 values = GetScale(iscale);
				EXPECT_NEAR(values.X(), 1.0 / ElementType(i), 0.001f);
				EXPECT_NEAR(values.Y(), 1.0 / ElementType(j), 0.001f);
				EXPECT_NEAR(values.Z(), 1.0 / ElementType(k), 0.001f);
			}
		}
	}
}


TYPED_TEST(Test_Matrix44v, InvertTranslation)
{
	using ElementType = typename TypeParam::ElementType;
	using Vector3 = Vector3v<typename TypeParam::SimdType>;

	// Test against scale matrices.
	for (int i = 1; i < 10; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			for (int k = 1; k < 10; ++k)
			{
				TypeParam scale = TypeParam::Translate(ElementType(i), ElementType(j), ElementType(k));
				TypeParam iscale = Invert(scale);

				Vector3 values = GetTranslation(iscale);
				EXPECT_NEAR(values.X(), -ElementType(i), 0.001f);
				EXPECT_NEAR(values.Y(), -ElementType(j), 0.001f);
				EXPECT_NEAR(values.Z(), -ElementType(k), 0.001f);
			}
		}
	}
}

#endif
