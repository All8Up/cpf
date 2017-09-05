//////////////////////////////////////////////////////////////////////////
#include <gmock/gmock.h>
#include "Patterns/Factory.hpp"

using namespace Cpf;
using namespace Patterns;

struct TestType
{

};

TEST(Patterns, Factory)
{
	using FactoryType = Factory<int64_t, TestType>;
	FactoryType testFactory;
	FactoryType::Entry installType{ []() {return new TestType; }, [](TestType&) {return false; } };
	EXPECT_TRUE(testFactory.Install(1, installType));
	EXPECT_TRUE(testFactory.Exists(1) == true);

	TestType* testType = nullptr;
	EXPECT_TRUE(testFactory.Create(1, &testType));
	EXPECT_TRUE(testType != nullptr);
	EXPECT_TRUE(testFactory.Remove(1));
	delete testType;
}
