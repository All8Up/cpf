//////////////////////////////////////////////////////////////////////////
#pragma once


namespace Cpf
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
			static constexpr float kPI = Math::kPI;
			static constexpr float kTwoPI = Math::kTwoPI;
			static constexpr float kDegToRad = Math::kDegToRad;
			static constexpr float kRadToDeg = Math::kRadToDeg;
			static constexpr float kHalfPI = Math::kHalfPI;
			static constexpr float kQuarterPI = Math::kQuarterPI;
			static constexpr float kOneOverPI = Math::kOneOverPI;
			static constexpr float kSqrtPI = Math::kSqrtPI;
			static constexpr float kSqrtTwoPI = Math::kSqrtTwoPI;
			static constexpr float kSqrtTwo = Math::kSqrtTwo;
			static constexpr float kSqrtThree = Math::kSqrtThree;
			static constexpr float kSqrtTen = Math::kSqrtTen;
			static constexpr float kSqrtE = Math::kSqrtE;
			static constexpr float kSqrtHalf = Math::kSqrtHalf;
			static constexpr float kSqrtLn2 = Math::kSqrtLn2;
			static constexpr float kE = Math::kE;
			static constexpr float kGolden = Math::kGolden;
			static constexpr float kLn10 = Math::kLn10;
			static constexpr float kLn2 = Math::kLn2;
			static constexpr float kLog10E = Math::kLog10E;
			static constexpr float kLog2E = Math::kLog2E;
			static constexpr float kLogP5 = Math::kLogP5;
			static constexpr float kC = Math::kC;
		};


		template<>
		struct Constants< double >
		{
			static constexpr double kPI = Math::kPI_d;
			static constexpr double kTwoPI = Math::kTwoPI_d;
			static constexpr double kDegToRad = Math::kDegToRad_d;
			static constexpr double kRadToDeg = Math::kRadToDeg_d;
			static constexpr double kHalfPI = Math::kHalfPI_d;
			static constexpr double kQuarterPI = Math::kQuarterPI_d;
			static constexpr double kOneOverPI = Math::kOneOverPI_d;
			static constexpr double kSqrtPI = Math::kSqrtPI_d;
			static constexpr double kSqrtTwoPI = Math::kSqrtTwoPI_d;
			static constexpr double kSqrtTwo = Math::kSqrtTwo_d;
			static constexpr double kSqrtThree = Math::kSqrtThree_d;
			static constexpr double kSqrtTen = Math::kSqrtTen_d;
			static constexpr double kSqrtE = Math::kSqrtE_d;
			static constexpr double kSqrtHalf = Math::kSqrtHalf_d;
			static constexpr double kSqrtLn2 = Math::kSqrtLn2_d;
			static constexpr double kE = Math::kE_d;
			static constexpr double kGolden = Math::kGolden_d;
			static constexpr double kLn10 = Math::kLn10_d;
			static constexpr double kLn2 = Math::kLn2_d;
			static constexpr double kLog10E = Math::kLog10E_d;
			static constexpr double kLog2E = Math::kLog2E_d;
			static constexpr double kLogP5 = Math::kLogP5_d;
			static constexpr double kC = Math::kC_d;
		};
	}
}
