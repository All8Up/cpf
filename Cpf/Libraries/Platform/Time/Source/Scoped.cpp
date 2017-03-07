//////////////////////////////////////////////////////////////////////////
#include "Time/Scoped.hpp"

using namespace Cpf;
using namespace Time;

//////////////////////////////////////////////////////////////////////////
/**
@brief ScopedNull constructor.
@param value Ignored reference.
*/
CPF_EXPORT_TIME ScopedNull::ScopedNull(Value&)
{
}


/**
@brief Return the start time, for Null this is always zero value.
*/
CPF_EXPORT_TIME Value& ScopedNull::Start()
{
	static Value zero;
	return zero;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief Constructor.
@param value Reference to the value where the result will be stored.
*/
CPF_EXPORT_TIME Action::Store::Store(Time::Value& value)
	: mValue(value)
{}


/**
@brief Operator to update the action.
@param duration Time since last execution, stored in reference value.
*/
CPF_EXPORT_TIME void Action::Store::operator ()(const Time::Value& duration)
{
	mValue = duration;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief Constructor.
@param value Reference to the value where the result will be added.
*/
CPF_EXPORT_TIME Action::Add::Add(Time::Value& value)
	: mValue(value)
{}


/**
@brief Operator to update the action.
@param duration Time since last execution, addition is made to the reference value.
*/
CPF_EXPORT_TIME void Action::Add::operator ()(const Time::Value& duration)
{
	mValue += duration;
}
