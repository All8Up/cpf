//////////////////////////////////////////////////////////////////////////
#include "Graphics/Ratio.hpp"

using namespace Cpf;
using namespace Graphics;

Ratio::Ratio()
	: mNumerator(1)
	, mDenominator(1)
{}

Ratio::Ratio(int32_t num, int32_t denom)
	: mNumerator(num)
	, mDenominator(denom)
{}

Ratio::operator float() const
{
	return float(mNumerator) / float(mDenominator);
}
