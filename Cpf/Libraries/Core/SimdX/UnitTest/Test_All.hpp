//////////////////////////////////////////////////////////////////////////
#include <gtest\gtest.h>
#include "SimdX.hpp"

static float temp = 0.0f;
TEST(SimdX, Float32x4)
{
	using namespace Cpf;
	using namespace SIMD;

	Float32x4 a{ 1.0f, 2.0f, 3.0f, 4.0f };
	EXPECT_NEAR(a.x, 1.0f, 0.01f);
	EXPECT_NEAR(a.y, 2.0f, 0.01f);
	EXPECT_NEAR(a.z, 3.0f, 0.01f);
	EXPECT_NEAR(a.w, 4.0f, 0.01f);

	a.x = 5.0f;
	a.y = 6.0f;
	a.z = 7.0f;
	a.w = 8.0f;

	EXPECT_NEAR(a.x, 5.0f, 0.01f);
	EXPECT_NEAR(a.y, 6.0f, 0.01f);
	EXPECT_NEAR(a.z, 7.0f, 0.01f);
	EXPECT_NEAR(a.w, 8.0f, 0.01f);

	temp = a.x + a.y + a.z + a.w;

	/* Produced assembly if you remove the unit testing:  Looks pretty damned good.
	00007FF78A906A20  movaps      xmm4,xmmword ptr [__xmm@4080000040400000400000003f800000 (07FF78A94FEF0h)]
	00007FF78A906A27  insertps    xmm4,dword ptr [__xmm@40a0000040a0000040a0000040a00000 (07FF78A950BD0h)],0
	00007FF78A906A31  insertps    xmm4,dword ptr [__xmm@40c0000040c0000040c0000040c00000 (07FF78A950BE0h)],10h
	00007FF78A906A3B  insertps    xmm4,dword ptr [__xmm@40e0000040e0000040e0000040e00000 (07FF78A950BF0h)],20h
	00007FF78A906A45  insertps    xmm4,dword ptr [__xmm@41000000410000004100000041000000 (07FF78A950C00h)],30h
	00007FF78A906A4F  extractps   dword ptr [rsp+10h],xmm4,1
	00007FF78A906A57  movss       xmm0,dword ptr [rsp+10h]
	00007FF78A906A5D  addss       xmm0,xmm4
	00007FF78A906A61  extractps   dword ptr [rsp+18h],xmm4,2
	00007FF78A906A69  extractps   dword ptr [rsp+20h],xmm4,3
	00007FF78A906A71  addss       xmm0,dword ptr [rsp+18h]
	00007FF78A906A77  addss       xmm0,dword ptr [rsp+20h]
	00007FF78A906A7D  movss       dword ptr [temp (07FF78A969598h)],xmm0
	*/
}
