//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Time.hpp"
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
		Cpf::TimeInitializer::Install();
	}
	virtual void TearDown() override
	{
		Cpf::TimeInitializer::Remove();
	}

	Cpf::Time::Ns oneNs;
	Cpf::Time::Us oneUs;
	Cpf::Time::Ms oneMs;
	Cpf::Time::Seconds oneSecond;
	Cpf::Time::Minutes oneMinute;
	Cpf::Time::Hours oneHour;
	Cpf::Time::Days oneDay;
	Cpf::Time::Years oneYear;
};


#include "Test_Value.hpp"
#include "Test_Unit_Us.hpp"
#include "Test_Different_Unit_Comparison.hpp"
