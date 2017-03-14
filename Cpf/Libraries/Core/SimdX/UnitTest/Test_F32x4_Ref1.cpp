//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Ref32x4_1 : public::testing::Test
{
public:
	using Type = typename TypeParam;
};

typedef ::testing::Types <
	Cpf::SIMD::Reference::F32x4_4,
	Cpf::SIMD::SSE4_1::F32x4_4,
//	Cpf::SIMD::Reference::I32x4_4,
	Cpf::SIMD::SSE4_1::I32x4_4
> Ref32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Ref32x4_1, Ref32x4_1_Types);


TYPED_TEST(TypedTest_Ref32x4_1, Construction)
{
}
