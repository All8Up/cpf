//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Time/Unit.hpp"
#include <gtest/gtest.h>

class TimeTestFixture : public ::testing::Test
{
public:
	TimeTestFixture()
	: oneNs(1)
	, oneUs(1)
	, oneMs(1)
	, oneSecond(1)
	, oneMinute(1)
	, oneHour(1)
	, oneDay(1)
	, oneYear(1)
	{}

	virtual void SetUp() override
	{
	}
	virtual void TearDown() override
	{
	}

	CPF::Time::Ns oneNs;
	CPF::Time::Us oneUs;
	CPF::Time::Ms oneMs;
	CPF::Time::Seconds oneSecond;
	CPF::Time::Minutes oneMinute;
	CPF::Time::Hours oneHour;
	CPF::Time::Days oneDay;
	CPF::Time::Years oneYear;
};
