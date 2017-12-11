#include <gtest/gtest.h>
#include "CPF/GOM/ResultCodes.hpp"

using namespace CPF;

TEST(GOM, Info)
{
	auto error = GOM::GetError(GOM::kOK);
	auto subsystem = GOM::GetSubSystem(GOM::kOK);
	auto code = GOM::GetCode(GOM::kOK);

	EXPECT_EQ(0, error);
	EXPECT_EQ(31560, subsystem);
	EXPECT_EQ(58943, code);
}
