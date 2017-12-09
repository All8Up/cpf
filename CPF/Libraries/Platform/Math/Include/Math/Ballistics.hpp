//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Constants.hpp"
#include "Math/Trigonometric.hpp"
#include "Math/Power.hpp"

namespace CPF
{
	namespace Math
	{
		namespace Ballistics
		{
			/*
			 * Rifleman's Rule:
			 * 	This is an approximation for solving non-level ballistics problems.
			 *
			 * The basic equation:  Rh = Rs * cos( A )
			 *
			 * Variables:
			 * Rh	=	Range to target horizontally.
			 * Rs	=	Range to target on slant.
			 * A	=	Horizontal angle between source and target.  (Radians)
			 *
			 * Variables used in variation functions:
			 * R	=	range of entire arc.
			 * T	=	time to peak of arc.
			 * T2	=	time of entire arc.
			 * Ct	=	current time.
			 * G	=	gravity constant.
			 * A	=	angle (in RADIANS) of initial velocity.
			 * P	=	peak height of arc.
			 * V	=	initial velocity.
			 * Vy	=	initial vertical velocity.
			 * Vx	=	initial horizontal velocity.
			 * X	=	position x
			 * Y	=	position y
			 * Ty	=	target y height
			 */

			template <typename T>
			inline T SolveTFromVyG(T vy, T g)
			{
				return vy / g;
			}

			template <typename T>
			inline T SolveTFromVxR(T vx, T r)
			{
				return r / vx;
			}

			template <typename T>
			inline T SolveT2FromVyG(T vy, T g)
			{
				return T(2) * (vy / g);
			}

			template <typename T>
			inline T SolveRFromVAG(T v, T a, T g)
			{
				return ((v*v) * Sin<T>(T(2)*a)) / g;
			}

			template <typename T>
			inline T SolvePFromVyG(T vy, T g)
			{
				return (vy*vy) / (T(2)*g);
			}

			template <typename T>
			inline T SolveVFromRAG(T r, T a, T g)
			{
				return Sqrt<T>((r*g) / Sin<T>(T(2)*a));
			}

			template <typename T>
			inline T SolveXFromVxCt(T vx, T Ct)
			{
				return vx*Ct;
			}

			template <typename T>
			inline T SolveYFromVyCtG(T vy, T Ct, T g)
			{
				return vy * Ct - (T(0.5) * g * (Ct*Ct));
			}

			template <typename T>
			inline void SolveAFromVRG(T v, T r, T g, T& a0, T& a1)
			{
				const T	a = ASin<T>((r*g) / (v*v));
				a0 = a;
				a1 = Constants<T>::kHalfPI - a;
			}

			template <typename T>
			inline bool SolveAFromVRGTy(T v, T r, T g, T y, T& a0, T& a1)
			{
				T v2 = v*v;
				T v4 = v2*v2;
				T r2 = r*r;
				T partial = v4 - (g * (g*r2 + 2 * y*v2));

				// If the partial is negative, there is not enough velocity to get to target.
				if (partial <= T(0))
					return false;

				T root = Sqrt(partial);
				T pos = (v2 + root) / (g*r);
				T neg = (v2 - root) / (g*r);

				a0 = ATan<T>(pos);
				a1 = ATan<T>(neg);
				return true;
			}

			template <typename T>
			inline void SolveAVFromVRGTy(T v, T vStep, T r, T g, T y, T& outV, T& a0, T& a1)
			{
				outV = v;
				while (!SolveAFromVRGTy(outV, r, g, y, a0, a1))
				{
					outV += vStep;
				};
			}

			template <typename T>
			inline T SolveRhFromRsA(T rs, T a)
			{
				return rs * Cos<T>(a);
			}

			template <typename T>
			inline T SolveAFromRhRs(T rh, T rs)
			{
				return ACos<T>(rh / rs);
			}
		}
	}
}
