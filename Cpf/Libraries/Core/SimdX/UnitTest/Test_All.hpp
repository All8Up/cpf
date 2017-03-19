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
	float hitT = 0.0f;

	Vector3v<F32x4_3> d0 = (bbmin - rayOrg) * invDir;
	Vector3v<F32x4_3> d1 = (bbmax - rayOrg) * invDir;

	Vector3v<F32x4_3> v0 = Min(d0, d1);
	Vector3v<F32x4_3> v1 = Max(d0, d1);

	auto tmin = HMax(v0);
	auto tmax = HMin(v1);

	hitT = tmin;
	bool hit = (tmax >= 0.0f) && (tmax >= tmin) && (tmin <= hitT);
	EXPECT_FALSE(hit);

	/* Current codegen, looks pretty decent but it is
	   spilling one register though, trying to figure it out.

	   00007FF61A5E3279  movaps      xmm4,xmmword ptr [__xmm@000000003f8000000000000000000000 (07FF61A659F50h)]
	   00007FF61A5E3280  movaps      xmm1,xmm4
	   00007FF61A5E3283  minps       xmm1,xmmword ptr [__xmm@00000000400000000000000000000000 (07FF61A662280h)]
	   00007FF61A5E328A  maxps       xmm4,xmmword ptr [__xmm@00000000400000000000000000000000 (07FF61A662280h)]
	   00007FF61A5E3291  movaps      xmm0,xmm1
	   00007FF61A5E3294  movhlps     xmm0,xmm1
	   00007FF61A5E3297  maxps       xmm1,xmm0
	   00007FF61A5E329A  shufps      xmm0,xmm0,1
	   00007FF61A5E329E  maxss       xmm1,xmm0
	   00007FF61A5E32A2  movaps      xmm0,xmm4
	   00007FF61A5E32A5  movhlps     xmm0,xmm4
	   00007FF61A5E32A8  movaps      xmm2,xmm4
	   00007FF61A5E32AB  minps       xmm2,xmm0
	   00007FF61A5E32AE  shufps      xmm4,xmm4,1
	   00007FF61A5E32B2  minss       xmm2,xmm4
	   00007FF61A5E32B6  movss       dword ptr [rsp+30h],xmm1
	   00007FF61A5E32BC  xorps       xmm0,xmm0
	   00007FF61A5E32BF  cmpleps     xmm0,xmm2
	   00007FF61A5E32C3  movmskps    eax,xmm0
	   00007FF61A5E32C6  test        al,1
	   00007FF61A5E32C8  je          SimdX_IntersectRayBox_Test::TestBody+0A1h (07FF61A5E32F1h)
	   00007FF61A5E32CA  movaps      xmm0,xmm1
	   00007FF61A5E32CD  cmpleps     xmm0,xmm2
	   00007FF61A5E32D1  movmskps    eax,xmm0
	   00007FF61A5E32D4  test        al,1
	   00007FF61A5E32D6  je          SimdX_IntersectRayBox_Test::TestBody+0A1h (07FF61A5E32F1h)
	   00007FF61A5E32D8  movss       xmm0,dword ptr [rsp+30h]
	   00007FF61A5E32DE  shufps      xmm0,xmm0,0
	   00007FF61A5E32E2  cmpleps     xmm1,xmm0
	   00007FF61A5E32E6  movmskps    eax,xmm1
	   00007FF61A5E32E9  test        al,1
	   00007FF61A5E32EB  je          SimdX_IntersectRayBox_Test::TestBody+0A1h (07FF61A5E32F1h)
	   00007FF61A5E32ED  mov         al,1
	   00007FF61A5E32EF  jmp         SimdX_IntersectRayBox_Test::TestBody+0A3h (07FF61A5E32F3h)
	   00007FF61A5E32F1  xor         al,al
	   */
}
