//////////////////////////////////////////////////////////////////////////
#include <gmock/gmock.h>
#include "EnumFlagType.hpp"

enum class TestType : int32_t
{
	eOne = 1,
	eTwo = 2,
	eThree = eOne + eTwo
};
CPF_ENUM_FLAG_TYPE(TestType);

TEST(EnumFlagType, Basics)
{
	TestType a(TestType::eOne);
	TestType b(TestType::eTwo);
	TestType c(a | b);

	EXPECT_EQ(c, TestType::eThree);
}
