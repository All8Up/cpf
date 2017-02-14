//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Constants.hpp"

namespace Cpf
{
	namespace Math
	{
		namespace Easing
		{
			namespace Out
			{
				template<typename TYPE>
				TYPE Linear(TYPE v);
				template<typename TYPE>
				TYPE Quadratic(TYPE v);
				template<typename TYPE>
				TYPE Cubic(TYPE v);
				template<typename TYPE>
				TYPE Quartic(TYPE v);
				template<typename TYPE>
				TYPE Quintic(TYPE v);
				template<typename TYPE>
				TYPE Sine(TYPE v);
				template<typename TYPE>
				TYPE Circular(TYPE v);
				template<typename TYPE>
				TYPE Exponential(TYPE v);
				template<typename TYPE>
				TYPE Elastic(TYPE v);
				template<typename TYPE>
				TYPE Overshoot(TYPE v);
				template<typename TYPE>
				TYPE Bounce(TYPE v);
			}
			namespace In
			{
				template<typename TYPE>
				inline TYPE Linear(TYPE v)
				{return v;}

				template<typename TYPE>
				inline TYPE Quadratic(TYPE v)
				{return v*v;}

				template<typename TYPE>
				inline TYPE Cubic(TYPE v)
				{return v*v*v;}

				template<typename TYPE>
				inline TYPE Quartic(TYPE v)
				{return v*v*v*v;}

				template<typename TYPE>
				inline TYPE Quintic(TYPE v)
				{return v*v*v*v*v;}

				template<typename TYPE>
				inline TYPE Sine(TYPE v)
				{return std::sin((v - TYPE(1)) * Constants<TYPE>::TwoPi()) + TYPE(1);}

				template<typename TYPE>
				inline TYPE Circular(TYPE v)
				{return TYPE(1) - std::sqrt(TYPE(1) - (v * v));}

				template<typename TYPE>
				inline TYPE Exponential(TYPE v)
				{(v == TYPE(0)) ? v : std::pow(TYPE(2), TYPE(10) * (v - TYPE(1)));}

				template<typename TYPE>
				inline TYPE Elastic(TYPE v)
				{ std::sin(TYPE(13) * Constants<TYPE>::TwoPi() * v) * std::pow(TYPE(2), TYPE(10) * (v - TYPE(1)));}

				template<typename TYPE>
				inline TYPE Overshoot(TYPE v)
				{return v * v * v - v * std::sin(v * Constants<TYPE>::Pi());}

				template<typename TYPE>
				inline TYPE Bounce(TYPE v)
				{return TYPE(1) - Out::Bounce<TYPE>(TYPE(1) - v);}
			}
			namespace InOut
			{
				template<typename TYPE>
				TYPE Linear(TYPE v);
				template<typename TYPE>
				TYPE Quadratic(TYPE v);
				template<typename TYPE>
				TYPE Cubic(TYPE v);
				template<typename TYPE>
				TYPE Quartic(TYPE v);
				template<typename TYPE>
				TYPE Quintic(TYPE v);
				template<typename TYPE>
				TYPE Sine(TYPE v);
				template<typename TYPE>
				TYPE Circular(TYPE v);
				template<typename TYPE>
				TYPE Exponential(TYPE v);
				template<typename TYPE>
				TYPE Elastic(TYPE v);
				template<typename TYPE>
				TYPE Overshoot(TYPE v);
				template<typename TYPE>
				TYPE Bounce(TYPE v);
			}
		}
	}
}
