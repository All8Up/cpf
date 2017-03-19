//////////////////////////////////////////////////////////////////////////
#pragma once
#include <gtest\gtest.h>
#include "SimdX.hpp"
#include "SIMD/Vector2v.hpp"
#include "SIMD/Vector3v.hpp"
#include "SIMD/Vector4v.hpp"

// Test code gen.
TEST(SimdX, IntersectRayBox)
{
	using namespace Cpf;
	using namespace Math;
	using namespace SIMD;

	Vector3v<F32x4_3> rayOrg(0.0f, 0.0f, 0.0f);
	Vector3v<F32x4_3> invDir(0.0f, 0.0f, 1.0f);
	Vector3v<F32x4_3> bbmin(5.0f, 5.0f, 1.0f);
	Vector3v<F32x4_3> bbmax(6.0f, 5.0f, 2.0f);

	Vector3v<F32x4_3> d0 = (bbmin - rayOrg) * invDir;
	Vector3v<F32x4_3> d1 = (bbmax - rayOrg) * invDir;

	Vector3v<F32x4_3> v0 = Min(d0, d1);
	Vector3v<F32x4_3> v1 = Max(d0, d1);

	auto tmin = HMax(v0);
	auto tmax = HMin(v1);

	auto hitT = tmin;
	bool hit = (tmax >= 0.0f) && (tmax >= tmin) && (tmin <= hitT);
	EXPECT_FALSE(hit);

	/* Current codegen, looks almost perfect now, auto is your friend in this case.
	   00007FF6FFA13279  movaps      xmm4,xmmword ptr [__xmm@000000003f8000000000000000000000 (07FF6FFA89F50h)]
	   00007FF6FFA13280  movaps      xmm1,xmm4
	   00007FF6FFA13283  minps       xmm1,xmmword ptr [__xmm@00000000400000000000000000000000 (07FF6FFA92280h)]
	   00007FF6FFA1328A  maxps       xmm4,xmmword ptr [__xmm@00000000400000000000000000000000 (07FF6FFA92280h)]
	   00007FF6FFA13291  movaps      xmm0,xmm1
	   00007FF6FFA13294  movhlps     xmm0,xmm1
	   00007FF6FFA13297  maxps       xmm1,xmm0
	   00007FF6FFA1329A  shufps      xmm0,xmm0,1
	   00007FF6FFA1329E  maxss       xmm1,xmm0
	   00007FF6FFA132A2  movaps      xmm0,xmm4
	   00007FF6FFA132A5  movhlps     xmm0,xmm4
	   00007FF6FFA132A8  movaps      xmm2,xmm4
	   00007FF6FFA132AB  minps       xmm2,xmm0
	   00007FF6FFA132AE  shufps      xmm4,xmm4,1
	   00007FF6FFA132B2  minss       xmm2,xmm4
	   00007FF6FFA132B6  xorps       xmm0,xmm0
	   00007FF6FFA132B9  cmpleps     xmm0,xmm2
	   00007FF6FFA132BD  movmskps    eax,xmm0
	   00007FF6FFA132C0  test        al,1
	   00007FF6FFA132C2  je          SimdX_IntersectRayBox_Test::TestBody+91h (07FF6FFA132E1h)
	   00007FF6FFA132C4  movaps      xmm0,xmm1
	   00007FF6FFA132C7  cmpleps     xmm0,xmm2
	   00007FF6FFA132CB  movmskps    eax,xmm0
	   00007FF6FFA132CE  test        al,1
	   00007FF6FFA132D0  je          SimdX_IntersectRayBox_Test::TestBody+91h (07FF6FFA132E1h)
	   00007FF6FFA132D2  cmpleps     xmm1,xmm1
	   00007FF6FFA132D6  movmskps    eax,xmm1
	   00007FF6FFA132D9  test        al,1
	   00007FF6FFA132DB  je          SimdX_IntersectRayBox_Test::TestBody+91h (07FF6FFA132E1h)
	   00007FF6FFA132DD  mov         al,1
	   00007FF6FFA132DF  jmp         SimdX_IntersectRayBox_Test::TestBody+93h (07FF6FFA132E3h)
	   00007FF6FFA132E1  xor         al,al
	   */
}
