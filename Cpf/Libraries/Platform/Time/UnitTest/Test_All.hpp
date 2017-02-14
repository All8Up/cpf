//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time/Time.hpp"
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
		Cpf::Platform::TimeInitializer::Install();
	}
	virtual void TearDown() override
	{
		Cpf::Platform::TimeInitializer::Remove();
	}

	Cpf::Platform::Time::Ns oneNs;
	Cpf::Platform::Time::Us oneUs;
	Cpf::Platform::Time::Ms oneMs;
	Cpf::Platform::Time::Seconds oneSecond;
	Cpf::Platform::Time::Minutes oneMinute;
	Cpf::Platform::Time::Hours oneHour;
	Cpf::Platform::Time::Days oneDay;
	Cpf::Platform::Time::Years oneYear;
};


#include "Test_Value.hpp"
#include "Test_Unit_Us.hpp"
#include "Test_Different_Unit_Comparison.hpp"
