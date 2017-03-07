//////////////////////////////////////////////////////////////////////////
#include "Time/Ratio.hpp"

using namespace Cpf;
using namespace Time;

Ratio::Ratio()
	: m_Numerator(0)
	, m_Denominator(0)
{}


/**
	* @brief Construct a ratio.
	* @param numerator The numerator used in the ratio.
	* @param denominator The denominator used in the ratio.
	*/
Ratio::Ratio(int64_t numerator, int64_t denominator)
	: m_Numerator(numerator)
	, m_Denominator(denominator)
{
	CPF_ASSERT(numerator != 0);
	CPF_ASSERT(denominator != 0);
}


/**
	* @brief Set the numerator of the ratio.
	*/
void Ratio::SetNumerator(int64_t value)
{
	CPF_ASSERT(value != 0);
	m_Numerator = value;
}


/**
	* @brief Get the numerator from the ratio.
	*/
int64_t Ratio::GetNumerator() const
{
	return m_Numerator;
}


/**
	* @brief Set the denominator of the ratio.
	*/
void Ratio::SetDenominator(int64_t value)
{
	CPF_ASSERT(value != 0);
	m_Denominator = value;
}


/**
	* @brief Get the denominator from the ratio.
	*/
int64_t Ratio::GetDenominator() const
{
	return m_Denominator;
}
