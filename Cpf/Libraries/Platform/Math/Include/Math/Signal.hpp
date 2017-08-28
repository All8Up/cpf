//////////////////////////////////////////////////////////////////////////
#pragma once

namespace Cpf
{
	namespace Math
	{
		template <typename T>
		inline T Step(T percentage, T a)
		{
			return((percentage >= a) ? T(1) : T(0));
		}

		template <typename T>
		inline T Pulse(T percentage, T a, T b)
		{
			return(Step(percentage, a) - Step(percentage, b));
		}

		template <typename T>
		inline T Smooth(T value)
		{
			return((T(3.0) - T(2.0)*value) * value * value);
		}

		template <typename T>
		inline T SmoothStep(T percentage, T a, T b)
		{
			return(percentage < T(0.0) ? a : (percentage > (T(1.0)) ? b : Lerp(Smooth(percentage), a, b));
		}

		template <typename T>
		inline T BoxStep(T a, T b, T x)
		{
			return(Clamp((x - a) / (b - a), T(0), T(1)));
		}

		template <typename T>
		inline T Gamma(T gamma, T x)
		{
			return(Pow(T(x), T(T(1) / gamma)));
		}

		template <typename T>
		inline T Bias(T b, T x)
		{
			return(Pow(T(x), Log(T(b)) / Log(T(0.5))));
		}

		template <typename T>
		inline T Gain(T g, T x)
		{
			if (x < T(0.5))
				return Bias(T(1) - g, 2 * x) / T(2);
			else
				return T(1) - Bias(T(1) - g, T(2) - T(2)*x) / T(2);
		}
	}
}
