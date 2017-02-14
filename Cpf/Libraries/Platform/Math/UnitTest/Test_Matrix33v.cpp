//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "Math/Matrix33v.hpp"
#include "Math/Constants.hpp"

using namespace Cpf::Math;

template <typename TYPE>
class Test_Matrix33v : public::testing::Test
{
public:
	Test_Matrix33v()
		: series(
			1, 2, 3,
			4, 5, 6,
			7, 8, 9
		)
	{
	}

	bool ValidateSeries(const TYPE& matrix)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				::testing::internal::FloatingPoint<typename TYPE::ElementType> lhs(matrix[i][j]);
				if (!lhs.AlmostEquals(::testing::internal::FloatingPoint<typename TYPE::ElementType>(typename TYPE::ElementType((i * 3 + j) + 1))))
					return false;
			}
		return true;
	}

	template<typename RHS>
	bool Compare(const TYPE& lhs, const RHS& rhs)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
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
	Matrix33fv
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
> Matrix33_Types;
TYPED_TEST_CASE(Test_Matrix33v, Matrix33_Types);


TYPED_TEST(Test_Matrix33v, RotateX)
{
	TypeParam test = TypeParam::RotateX(Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_NEAR(test[0][0], 1.0f, 0.01f);
	EXPECT_NEAR(test[0][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[0][2], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][2], 1.0f, 0.01f);
	EXPECT_NEAR(test[2][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][1], -1.0f, 0.01f);
	EXPECT_NEAR(test[2][2], 0.0f, 0.01f);

	TypeParam testaa = TypeParam::AxisAngle(TypeParam::RowType::XAxis(), Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_TRUE(this->Compare(test, testaa));
}

TYPED_TEST(Test_Matrix33v, RotateY)
{
	TypeParam test = TypeParam::RotateY(Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_NEAR(test[0][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[0][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[0][2], -1.0f, 0.01f);
	EXPECT_NEAR(test[1][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][1], 1.0f, 0.01f);
	EXPECT_NEAR(test[1][2], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][0], 1.0f, 0.01f);
	EXPECT_NEAR(test[2][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][2], 0.0f, 0.01f);

	TypeParam testaa = TypeParam::AxisAngle(TypeParam::RowType::YAxis(), Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_TRUE(this->Compare(test, testaa));
}

TYPED_TEST(Test_Matrix33v, RotateZ)
{
	TypeParam test = TypeParam::RotateZ(Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_NEAR(test[0][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[0][1], 1.0f, 0.01f);
	EXPECT_NEAR(test[0][2], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][0], -1.0f, 0.01f);
	EXPECT_NEAR(test[1][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[1][2], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][0], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][1], 0.0f, 0.01f);
	EXPECT_NEAR(test[2][2], 1.0f, 0.01f);

	TypeParam testaa = TypeParam::AxisAngle(TypeParam::RowType::ZAxis(), Constants<typename TypeParam::ElementType>::kDegToRad * 90);
	EXPECT_TRUE(this->Compare(test, testaa));
}
