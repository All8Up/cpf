//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "SIMD.hpp"
#include "Math/Vector2v.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"

// Test code gen.
TEST(SIMD, IntersectRayBox)
{
	using namespace Cpf;
	using namespace Math;
	using namespace SIMD;

	struct Test
	{
#if CPF_TARGET_WINDOWS
		__declspec(noinline)
#endif
		static bool  CPF_VECTORCALL Intersect(
			Vector3v<F32x4_3> rayOrg,
			Vector3v<F32x4_3> invDir,
			Vector3v<F32x4_3> bbmin,
			Vector3v<F32x4_3> bbmax,
			float& hitPoint
		)
		{
			Vector3v<F32x4_3> d0 = (bbmin - rayOrg) * invDir;
			Vector3v<F32x4_3> d1 = (bbmax - rayOrg) * invDir;

			Vector3v<F32x4_3> v0 = Min(d0, d1);
			Vector3v<F32x4_3> v1 = Max(d0, d1);

			auto tmin = HMax(v0);
			auto tmax = HMin(v1);

			if ((tmax >= 0.0f) && (tmax >= tmin) && (tmin <= hitPoint))
			{
				hitPoint = tmin;
				return true;
			}
			return false;
		}
	};

	Vector3v<F32x4_3> rayOrg(0.0f, 0.0f, 0.0f);
	Vector3v<F32x4_3> invDir(0.0f, 0.0f, 1.0f);
	Vector3v<F32x4_3> bbmin(5.0f, 5.0f, 1.0f);
	Vector3v<F32x4_3> bbmax(6.0f, 5.0f, 2.0f);
	float hitPoint;
	bool result = Test::Intersect(rayOrg, invDir, bbmin, bbmax, hitPoint);
	EXPECT_FALSE(result);

	/* Current codegen, looks almost perfect now, auto is your friend in this case.
	   NOTE: There are some items in the wrapper to be optimized still but this does
	   not seem to have any extraneous wastage on top of that.
	00007FF7C5C03720  movups      xmm2,xmmword ptr [r8]
	00007FF7C5C03724  subps       xmm2,xmmword ptr [rcx]
	00007FF7C5C03727  movups      xmm0,xmmword ptr [r9]
	00007FF7C5C0372B  subps       xmm0,xmmword ptr [rcx]
	00007FF7C5C0372E  mulps       xmm2,xmmword ptr [rdx]
	00007FF7C5C03731  mulps       xmm0,xmmword ptr [rdx]
	00007FF7C5C03734  movaps      xmm3,xmm2
	00007FF7C5C03737  minps       xmm3,xmm0
	00007FF7C5C0373A  maxps       xmm2,xmm0
	00007FF7C5C0373D  movaps      xmm1,xmm3
	00007FF7C5C03740  movhlps     xmm1,xmm3
	00007FF7C5C03743  maxps       xmm3,xmm1
	00007FF7C5C03746  movaps      xmm0,xmm1
	00007FF7C5C03749  shufps      xmm0,xmm1,1
	00007FF7C5C0374D  movaps      xmm1,xmm2
	00007FF7C5C03750  maxss       xmm3,xmm0
	00007FF7C5C03754  movaps      xmm0,xmm2
	00007FF7C5C03757  movhlps     xmm0,xmm2
	00007FF7C5C0375A  minps       xmm1,xmm0
	00007FF7C5C0375D  shufps      xmm2,xmm2,1
	00007FF7C5C03761  xorps       xmm0,xmm0
	00007FF7C5C03764  minss       xmm1,xmm2
	00007FF7C5C03768  cmpleps     xmm0,xmm1
	00007FF7C5C0376C  movmskps    eax,xmm0
	00007FF7C5C0376F  test        al,1
	00007FF7C5C03771  je          `SimdX_IntersectRayBox_Test::TestBody'::`2'::Test::Intersect+83h (07FF7C5C037A3h)
	00007FF7C5C03773  movaps      xmm0,xmm3
	00007FF7C5C03776  cmpleps     xmm0,xmm1
	00007FF7C5C0377A  movmskps    eax,xmm0
	00007FF7C5C0377D  test        al,1
	00007FF7C5C0377F  je          `SimdX_IntersectRayBox_Test::TestBody'::`2'::Test::Intersect+83h (07FF7C5C037A3h)
	00007FF7C5C03781  mov         rcx,qword ptr [hitPoint]
	00007FF7C5C03786  movaps      xmm1,xmm3
	00007FF7C5C03789  movss       xmm0,dword ptr [rcx]
	00007FF7C5C0378D  shufps      xmm0,xmm0,0
	00007FF7C5C03791  cmpleps     xmm1,xmm0
	00007FF7C5C03795  movmskps    eax,xmm1
	00007FF7C5C03798  test        al,1
	00007FF7C5C0379A  je          `SimdX_IntersectRayBox_Test::TestBody'::`2'::Test::Intersect+83h (07FF7C5C037A3h)
	00007FF7C5C0379C  movss       dword ptr [rcx],xmm3
	00007FF7C5C037A0  mov         al,1
	00007FF7C5C037A2  ret
	00007FF7C5C037A3  xor         al,al
	00007FF7C5C037A5  ret
	*/
}
