//////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>

namespace Cpf
{
	namespace Math
	{
		inline float Sin(float r) { return std::sin(r); }
		inline float Cos(float r) { return std::cos(r); }
		inline float Tan(float r) { return std::tan(r); }
		inline float ASin(float r) { return std::asin(r); }
		inline float ACos(float r) { return std::acos(r); }
		inline float ATan(float r) { return std::atan(r); }
		inline float ATan2(float x, float y) { return std::atan2(x, y); }
	}
}
