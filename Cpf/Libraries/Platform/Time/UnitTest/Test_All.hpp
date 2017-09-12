//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Unit.hpp"

class TimeLibrary : public ::testing::Test
{
public:
	TimeLibrary()
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


#include "Test_Value.hpp"
#include "Test_Unit_Us.hpp"
#include "Test_Different_Unit_Comparison.hpp"
