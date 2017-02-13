//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Atomic/Atomic.hpp"
#include <limits>


template<typename T>
class AtomicTest : public ::testing::Test
{

};
TYPED_TEST_CASE_P(AtomicTest);

TYPED_TEST_P(AtomicTest, Load)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	EXPECT_EQ(0, Atomic::Load(testValue));
	testValue = std::numeric_limits<TypeParam>::max();
	EXPECT_EQ(std::numeric_limits<TypeParam>::max(), Atomic::Load(testValue));
}


TYPED_TEST_P(AtomicTest, Store)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	Atomic::Store(testValue, std::numeric_limits<TypeParam>::max());
	EXPECT_EQ(std::numeric_limits<TypeParam>::max(), testValue);
}


TYPED_TEST_P(AtomicTest, Inc)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	EXPECT_EQ(1, Atomic::Inc(testValue));
	EXPECT_EQ(1, testValue);
}


TYPED_TEST_P(AtomicTest, Dec)
{
	using namespace Cpf;
	TypeParam testValue = std::numeric_limits<TypeParam>::max();
	EXPECT_EQ(std::numeric_limits<TypeParam>::max() - 1, Atomic::Dec(testValue));
	EXPECT_EQ(std::numeric_limits<TypeParam>::max() - 1, testValue);
}


TYPED_TEST_P(AtomicTest, Add)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	EXPECT_EQ(5, Atomic::Add(testValue, 5));
	EXPECT_EQ(5, testValue);
}


TYPED_TEST_P(AtomicTest, Sub)
{
	using namespace Cpf;
	TypeParam testValue = std::numeric_limits<TypeParam>::max();
	EXPECT_EQ(std::numeric_limits<TypeParam>::max() - 5, Atomic::Sub(testValue, 5));
	EXPECT_EQ(std::numeric_limits<TypeParam>::max() - 5, testValue);
}


TYPED_TEST_P(AtomicTest, Exchange)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	EXPECT_EQ(0, Atomic::Exchange(testValue, std::numeric_limits<TypeParam>::max()));
	EXPECT_EQ(std::numeric_limits<TypeParam>::max(), testValue);
}


TYPED_TEST_P(AtomicTest, CompareExchange)
{
	using namespace Cpf;
	TypeParam testValue = 0;
	EXPECT_TRUE(Atomic::CompareExchange(testValue, std::numeric_limits<TypeParam>::max(), 0));
	EXPECT_FALSE(Atomic::CompareExchange(testValue, std::numeric_limits<TypeParam>::max(), 0));
	EXPECT_EQ(std::numeric_limits<TypeParam>::max(), testValue);
}


//////////////////////////////////////////////////////////////////////////
REGISTER_TYPED_TEST_CASE_P(AtomicTest, Load, Store, Inc, Dec, Add, Sub, Exchange, CompareExchange);

typedef ::testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, size_t, intptr_t> AtomicTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(Atomics, AtomicTest, AtomicTestTypes);
