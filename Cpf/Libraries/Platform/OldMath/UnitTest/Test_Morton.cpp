#include "Math/Morton.hpp"
#include <gmock/gmock.h>

TEST(Math, Morton_EncodeDecode32_2D_Limits)
{
	using namespace Cpf::Math;
	int32_t x, y;

	// Zero
	EXPECT_EQ(0, Morton32Encode(0, 0));
	MortonDecode(Morton32Encode(0, 0), x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);

	// +Epsilon
	EXPECT_EQ(3, Morton32Encode(1, 1));
	MortonDecode(Morton32Encode(1, 1), x, y);
	EXPECT_EQ(1, x);
	EXPECT_EQ(1, y);

	// -Epsilon
	EXPECT_EQ(0xFFFFFFFF, Morton32Encode(-1, -1));
	MortonDecode(Morton32Encode(-1, -1), x, y);
	EXPECT_EQ(-1, x);
	EXPECT_EQ(-1, y);

	// Min
	EXPECT_EQ(0xC0000000, Morton32Encode(-32768, -32768));
	MortonDecode(Morton32Encode(-32768, -32768), x, y);
	EXPECT_EQ(-32768, x);
	EXPECT_EQ(-32768, y);

	// Max
	EXPECT_EQ(0x3FFFFFFF, Morton32Encode(32767, 32767));
	MortonDecode(Morton32Encode(32767, 32767), x, y);
	EXPECT_EQ(32767, x);
	EXPECT_EQ(32767, y);
}

TEST(Math, Morton_EncodeDecode64_2D_Limits)
{
	using namespace Cpf::Math;
	int32_t x, y;

	// Zero
	EXPECT_EQ(0, Morton64Encode(0, 0));
	MortonDecode(Morton64Encode(0, 0), x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);

	// +Epsilon
	EXPECT_EQ(3, Morton64Encode(1, 1));
	MortonDecode(Morton64Encode(1, 1), x, y);
	EXPECT_EQ(1, x);
	EXPECT_EQ(1, y);

	// -Epsilon
	EXPECT_EQ(0xFFFFFFFFFFFFFFFF, Morton64Encode(-1, -1));
	MortonDecode(Morton64Encode(-1, -1), x, y);
	EXPECT_EQ(-1, x);
	EXPECT_EQ(-1, y);

	// Min
	EXPECT_EQ(0xC000000000000000, Morton64Encode(0x80000000, 0x80000000));
	MortonDecode(Morton64Encode(0x80000000, 0x80000000), x, y);
	EXPECT_EQ(0x80000000, x);
	EXPECT_EQ(0x80000000, y);

	// Max
	EXPECT_EQ(0x3FFFFFFFFFFFFFFF, Morton64Encode(2147483647, 2147483647));
	MortonDecode(Morton64Encode(2147483647, 2147483647), x, y);
	EXPECT_EQ(2147483647, x);
	EXPECT_EQ(2147483647, y);
}

TEST(Math, Morton_EncodeDecode32_3D_Limits)
{
	using namespace Cpf::Math;
	int32_t x, y, z;

	// Zero
	EXPECT_EQ(0, Morton32Encode(0, 0, 0));
	MortonDecode(Morton32Encode(0, 0, 0), x, y, z);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);
	EXPECT_EQ(0, z);

	// +Epsilon
	EXPECT_EQ(7, Morton32Encode(1, 1, 1));
	MortonDecode(Morton32Encode(1, 1, 1), x, y, z);
	EXPECT_EQ(1, x);
	EXPECT_EQ(1, y);
	EXPECT_EQ(1, z);

	// -Epsilon
	EXPECT_EQ(0x3FFFFFFF, Morton32Encode(-1, -1, -1));
	MortonDecode(Morton32Encode(-1, -1, -1), x, y, z);
	EXPECT_EQ(-1, x);
	EXPECT_EQ(-1, y);
	EXPECT_EQ(-1, z);

	// Min
	EXPECT_EQ(0x38000000, Morton32Encode(-512, -512, -512));
	MortonDecode(Morton32Encode(-512, -512, -512), x, y, z);
	EXPECT_EQ(-512, x);
	EXPECT_EQ(-512, y);
	EXPECT_EQ(-512, z);

	// Max
	EXPECT_EQ(0x07ffffff, Morton32Encode(511, 511, 511));
	MortonDecode(Morton32Encode(511, 511, 511), x, y, z);
	EXPECT_EQ(511, x);
	EXPECT_EQ(511, y);
	EXPECT_EQ(511, z);
}

TEST(Math, Morton_EncodeDecode64_3D_Limits)
{
	using namespace Cpf::Math;
	int32_t x, y, z;

	// Zero
	EXPECT_EQ(0, Morton64Encode(0, 0, 0));
	MortonDecode(Morton64Encode(0, 0, 0), x, y, z);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);
	EXPECT_EQ(0, z);

	// +Epsilon
	EXPECT_EQ(7, Morton64Encode(1, 1, 1));
	MortonDecode(Morton64Encode(1, 1, 1), x, y, z);
	EXPECT_EQ(1, x);
	EXPECT_EQ(1, y);
	EXPECT_EQ(1, z);

	// -Epsilon
	EXPECT_EQ(0x7fffffffffffffff, Morton64Encode(-1, -1, -1));
	MortonDecode(Morton64Encode(-1, -1, -1), x, y, z);
	EXPECT_EQ(-1, x);
	EXPECT_EQ(-1, y);
	EXPECT_EQ(-1, z);

	// Min
	EXPECT_EQ(0x7000000000000000, Morton64Encode(-1048576, -1048576, -1048576));
	MortonDecode(Morton64Encode(-1048576, -1048576, -1048576), x, y, z);
	EXPECT_EQ(-1048576, x);
	EXPECT_EQ(-1048576, y);
	EXPECT_EQ(-1048576, z);

	// Max
	EXPECT_EQ(0x0fffffffffffffff, Morton64Encode(1048575, 1048575, 1048575));
	MortonDecode(Morton64Encode(1048575, 1048575, 1048575), x, y, z);
	EXPECT_EQ(1048575, x);
	EXPECT_EQ(1048575, y);
	EXPECT_EQ(1048575, z);
}
