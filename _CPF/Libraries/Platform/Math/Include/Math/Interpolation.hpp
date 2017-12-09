//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE, typename PTYPE>
		TYPE Lerp(TYPE lhs, TYPE rhs, PTYPE percent)
		{
			return lhs + (rhs - lhs) * percent;
		}

		template <typename T, typename M>
		inline T Hermite(T v1, T t1, T v2, T t2, M s)
		{
			T s2 = s*s;
			T s3 = s2*s;
			T b0 = (2 * s3) - (3 * s2) + 1;
			T b1 = -(2 * s3) + (3 * s2);
			T b2 = (s3)-(2 * s2) + s;
			T b3 = (s3)-(s2);

			return(b0*v1 + b1*v2 + b2*t1 + b3*t2);
		}

		template <typename T, typename D>
		inline D Spline(size_t count, D knots[], T x)
		{
			// Coefficients.
			D CR00 = -D(0.5);
			D CR01 = D(1.5);
			D CR02 = -D(1.5);
			D CR03 = D(0.5);
			D CR10 = D(1);
			D CR11 = -D(2.5);
			D CR12 = D(2);
			D CR13 = -D(0.5);
			D CR20 = -D(0.5);
			D CR21 = D(0);
			D CR22 = D(0.5);
			D CR23 = D(0);
			D CR30 = D(0);
			D CR31 = D(1);
			D CR32 = D(0);
			D CR33 = D(0);

			size_t nspans = count - 3;
			if (nspans < 1)
			{
				CPF_ASSERT_ALWAYS;	// This is not right!
				return D(0);
			}

			T cx = Clamp<T>(x, 0, 1);
			size_t span = (size_t)cx;

			if (span >= count - 3)
				span = count - 3;
			cx -= span;

			D c3 = CR00*knots[span] + CR01*knots[span + 1] +
				CR02*knots[span + 2] + CR03*knots[span + 3];
			D c2 = CR10*knots[span] + CR11*knots[span + 1] +
				CR12*knots[span + 2] + CR13*knots[span + 3];
			D c1 = CR20*knots[span] + CR21*knots[span + 1] +
				CR22*knots[span + 2] + CR23*knots[span + 3];
			D c0 = CR30*knots[span] + CR31*knots[span + 1] +
				CR32*knots[span + 2] + CR33*knots[span + 3];

			return(((c3*cx + c2)*cx + c1)*cx + c0);
		}
	}
}
