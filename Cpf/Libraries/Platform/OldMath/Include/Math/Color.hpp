//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"


namespace Cpf
{
	namespace Math
	{
		class Color3f
		{
		public:
			Color3f() {}
			Color3f(float r, float g, float b)
				: mR(r)
				, mG(g)
				, mB(b)
			{}
			Color3f(const Color3f& rhs)
				: mR(rhs.mR)
				, mG(rhs.mG)
				, mB(rhs.mB)
			{}

			Color3f& operator =(const Color3f& rhs)
			{
				mR = rhs.mR;
				mG = rhs.mG;
				mB = rhs.mB;
				return *this;
			}

			Color3f& Set(float r, float g, float b)
			{
				mR = r;
				mG = g;
				mB = b;
				return *this;
			}

			float R() const {return mR;}
			void R(float r) {mR = r;}
			float G() const {return mG;}
			void G(float g) {mG = g;}
			float B() const {return mB;}
			void B(float b) {mB = b;}

			Color3f operator +(const Color3f& rhs) const
			{
				return Color3f(mR+rhs.mR, mG+rhs.mG, mB+rhs.mB);
			}
			Color3f operator -(const Color3f& rhs) const
			{
				return Color3f(mR-rhs.mR, mG-rhs.mG, mB-rhs.mB);
			}
			Color3f operator *(float rhs) const
			{
				return Color3f(mR*rhs, mG*rhs, mB*rhs);
			}
			Color3f operator /(float rhs) const
			{
				return Color3f(mR/rhs, mG/rhs, mB/rhs);
			}

			//
			float mR;
			float mG;
			float mB;
		};

		class Color4f
		{
		public:
			Color4f() {}
			Color4f(float r, float g, float b, float a)
				: mR(r)
				, mG(g)
				, mB(b)
				, mA(a)
			{}
			Color4f(const Color4f& rhs)
				: mR(rhs.mR)
				, mG(rhs.mG)
				, mB(rhs.mB)
				, mA(rhs.mA)
			{}

			Color4f& operator =(const Color4f& rhs)
			{
				mR = rhs.mR;
				mG = rhs.mG;
				mB = rhs.mB;
				mA = rhs.mA;
				return *this;
			}

			Color4f& Set(float r, float g, float b, float a)
			{
				mR = r;
				mG = g;
				mB = b;
				mA = a;
				return *this;
			}

			float R() const { return mR; }
			void R(float r) { mR = r; }
			float G() const { return mG; }
			void G(float g) { mG = g; }
			float B() const { return mB; }
			void B(float b) { mB = b; }
			float A() const { return mA; }
			void A(float a) { mA = a; }

			Color4f operator +(const Color4f& rhs) const
			{
				return Color4f(mR + rhs.mR, mG + rhs.mG, mB + rhs.mB, mA + rhs.mA);
			}
			Color4f operator -(const Color4f& rhs) const
			{
				return Color4f(mR - rhs.mR, mG - rhs.mG, mB - rhs.mB, mA - rhs.mA);
			}
			Color4f operator *(float rhs) const
			{
				return Color4f(mR*rhs, mG*rhs, mB*rhs, mA*rhs);
			}
			Color4f operator /(float rhs) const
			{
				return Color4f(mR / rhs, mG / rhs, mB / rhs, mA / rhs);
			}

			//
			float mR;
			float mG;
			float mB;
			float mA;
		};
	}
}
