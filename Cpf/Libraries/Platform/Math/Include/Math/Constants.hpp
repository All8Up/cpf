//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace CPF
{
	namespace Math
	{
		static constexpr float kPI = 3.14159265358979323846f;
		static constexpr float kTwoPI = 6.28318530717958623200f;
		static constexpr float kDegToRad = kPI / 180.0f;
		static constexpr float kRadToDeg = 180.0f / kPI;
		static constexpr float kHalfPI = 1.57079632679489655800f;
		static constexpr float kQuarterPI = 0.78539816339744827900f;
		static constexpr float kOneOverPI = 0.31830988618379069122f;
		static constexpr float kSqrtPI = 1.77245385090551588192f;
		static constexpr float kSqrtTwoPI = 2.50662827463100024161f;
		static constexpr float kSqrtTwo = 1.41421356237309514547f;
		static constexpr float kSqrtThree = 1.73205080756887719318f;
		static constexpr float kSqrtTen = 3.16227766016837952279f;
		static constexpr float kSqrtE = 1.64872127070012819416f;
		static constexpr float kSqrtHalf = 0.70710678118654757274f;
		static constexpr float kSqrtLn2 = 0.83255461115769768821f;
		static constexpr float kE = 2.71828182845904553488f;
		static constexpr float kGolden = 1.61803398874989490253f;
		static constexpr float kLn10 = 2.30258509299404590109f;
		static constexpr float kLn2 = 0.69314718055994528623f;
		static constexpr float kLog10E = 0.43429448190325187218f;
		static constexpr float kLog2E = 1.44269504088896338700f;
		static constexpr float kLogP5 = -0.693147f;
		static constexpr float kC = 299792458.0f;
		static constexpr float kFloatMax = 3.402823466e+38f;

		static constexpr double kPI_d = 3.14159265358979323846;
		static constexpr double kTwoPI_d = 6.28318530717958623200;
		static constexpr double kHalfPI_d = 1.57079632679489655800;
		static constexpr double kQuarterPI_d = 0.78539816339744827900;
		static constexpr double kOneOverPI_d = 0.31830988618379069122;
		static constexpr double kSqrtPI_d = 1.77245385090551588192;
		static constexpr double kSqrtTwoPI_d = 2.50662827463100024161;
		static constexpr double kSqrtTwo_d = 1.41421356237309514547;
		static constexpr double kSqrtThree_d = 1.73205080756887719318;
		static constexpr double kSqrtTen_d = 3.16227766016837952279;
		static constexpr double kSqrtE_d = 1.64872127070012819416;
		static constexpr double kSqrtHalf_d = 0.70710678118654757274;
		static constexpr double kSqrtLn2_d = 0.83255461115769768821;
		static constexpr double kE_d = 2.71828182845904553488;
		static constexpr double kGolden_d = 1.61803398874989490253;
		static constexpr double kLn10_d = 2.30258509299404590109;
		static constexpr double kLn2_d = 0.69314718055994528623;
		static constexpr double kLog10E_d = 0.43429448190325187218;
		static constexpr double kLog2E_d = 1.44269504088896338700;
		static constexpr double kLogP5_d = -0.693147;
		static constexpr double kC_d = 299792458.0;
		static constexpr double kDegToRad_d = kPI_d / 180.0;
		static constexpr double kRadToDeg_d = 180.0 / kPI_d;

		//////////////////////////////////////////////////////////////////////////
		// Wrappers for template usage.
		template<typename T> struct Constants;

		template<>
		struct Constants< float >
		{
			static constexpr float kPI = kPI;
			static constexpr float kTwoPI = kTwoPI;
			static constexpr float kDegToRad = kDegToRad;
			static constexpr float kRadToDeg = kRadToDeg;
			static constexpr float kHalfPI = kHalfPI;
			static constexpr float kQuarterPI = kQuarterPI;
			static constexpr float kOneOverPI = kOneOverPI;
			static constexpr float kSqrtPI = kSqrtPI;
			static constexpr float kSqrtTwoPI = kSqrtTwoPI;
			static constexpr float kSqrtTwo = kSqrtTwo;
			static constexpr float kSqrtThree = kSqrtThree;
			static constexpr float kSqrtTen = kSqrtTen;
			static constexpr float kSqrtE = kSqrtE;
			static constexpr float kSqrtHalf = kSqrtHalf;
			static constexpr float kSqrtLn2 = kSqrtLn2;
			static constexpr float kE = kE;
			static constexpr float kGolden = kGolden;
			static constexpr float kLn10 = kLn10;
			static constexpr float kLn2 = kLn2;
			static constexpr float kLog10E = kLog10E;
			static constexpr float kLog2E = kLog2E;
			static constexpr float kLogP5 = kLogP5;
			static constexpr float kC = kC;
		};


		template<>
		struct Constants< double >
		{
			static constexpr double kPI = kPI_d;
			static constexpr double kTwoPI = kTwoPI_d;
			static constexpr double kDegToRad = kDegToRad_d;
			static constexpr double kRadToDeg = kRadToDeg_d;
			static constexpr double kHalfPI = kHalfPI_d;
			static constexpr double kQuarterPI = kQuarterPI_d;
			static constexpr double kOneOverPI = kOneOverPI_d;
			static constexpr double kSqrtPI = kSqrtPI_d;
			static constexpr double kSqrtTwoPI = kSqrtTwoPI_d;
			static constexpr double kSqrtTwo = kSqrtTwo_d;
			static constexpr double kSqrtThree = kSqrtThree_d;
			static constexpr double kSqrtTen = kSqrtTen_d;
			static constexpr double kSqrtE = kSqrtE_d;
			static constexpr double kSqrtHalf = kSqrtHalf_d;
			static constexpr double kSqrtLn2 = kSqrtLn2_d;
			static constexpr double kE = kE_d;
			static constexpr double kGolden = kGolden_d;
			static constexpr double kLn10 = kLn10_d;
			static constexpr double kLn2 = kLn2_d;
			static constexpr double kLog10E = kLog10E_d;
			static constexpr double kLog2E = kLog2E_d;
			static constexpr double kLogP5 = kLogP5_d;
			static constexpr double kC = kC_d;
		};
	}
}
