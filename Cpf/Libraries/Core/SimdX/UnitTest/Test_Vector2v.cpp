//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"

//////////////////////////////////////////////////////////////////////////
template <typename T>
class TypedTest_Vector2v : public::testing::Test
{
public:
};

typedef ::testing::Types <
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::F32x4_4>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::F32x4_4>,
	Cpf::Math::Vector2v<Cpf::SIMD::Reference::I32x4_4>,
	Cpf::Math::Vector2v<Cpf::SIMD::SSE4_1::I32x4_4>
> F32x4_1_Types;

TYPED_TEST_CASE(TypedTest_Vector2v, F32x4_1_Types);


TYPED_TEST(TypedTest_Vector2v, Construction)
{
	using Type = typename TypeParam;
	using Element = typename Type::Element;
}
