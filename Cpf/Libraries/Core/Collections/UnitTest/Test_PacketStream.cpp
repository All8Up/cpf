//////////////////////////////////////////////////////////////////////////
#include "gmock/gmock.h"
#include "PacketStream.hpp"

namespace
{
	bool testResult[3] = { false };

	struct A
	{
		int32_t i;
		int32_t b;

		void operator ()(int, int) const
		{
			testResult[0] = true;
		}
	};

	struct B
	{
		int32_t a;
		int64_t b;

		void operator ()(int, int) const
		{
			testResult[1] = true;
		}
	};

	struct AA : A
	{
		AA(int32_t _i, int32_t _b, int64_t _c) : A{ _i, _b }, c(_c) {}

		int64_t c;

		void operator ()(int, int) const
		{
			testResult[2] = true;
		}
	};

	using TestPacketTypes = Cpf::PacketTypes <A, B, AA>;
}

#if 0
TEST(Collections, PacketTypeList_IndexOf)
{
	EXPECT_TRUE(TestPacketTypes::IndexOf<A>() == 0);
	EXPECT_TRUE(TestPacketTypes::IndexOf<B>() == 1);
	EXPECT_TRUE(TestPacketTypes::IndexOf<AA>() == 2);
}

TEST(Collections, PacketTypeList_SizeOfTemplated)
{
	EXPECT_TRUE(sizeof(A) == TestPacketTypes::SizeOf(0));
	EXPECT_TRUE(sizeof(B) == TestPacketTypes::SizeOf(1));
	EXPECT_TRUE(sizeof(AA) == TestPacketTypes::SizeOf(2));
}

TEST(Collections, PacketTypeList_SizeOfIndexed)
{
	EXPECT_TRUE(sizeof(A) == TestPacketTypes::SizeOf(0));
	EXPECT_TRUE(sizeof(B) == TestPacketTypes::SizeOf(1));
	EXPECT_TRUE(sizeof(AA) == TestPacketTypes::SizeOf(2));
}

TEST(Collections, PacketWrapper)
{
	using namespace Cpf;
	Packet<A, TestPacketTypes> a({
		12, 27
	});
	EXPECT_TRUE(a.TypeIndex() == 0);

	Packet<B, TestPacketTypes> b({
		5, 3
	});
	EXPECT_TRUE(b.TypeIndex() == 1);

	Packet<AA, TestPacketTypes> aa({
		15, 31, 9
	});
	EXPECT_TRUE(aa.TypeIndex() == 2);

	EXPECT_TRUE(sizeof(a) == TestPacketTypes::SizeOf(0));
	EXPECT_TRUE(sizeof(b) == TestPacketTypes::SizeOf(1));
	EXPECT_TRUE(sizeof(aa) == TestPacketTypes::SizeOf(2));
}

TEST(Collections, PacketStream_EncodeAndDecode)
{
	using namespace Cpf;

	PacketStream<TestPacketTypes> ps;
	ps << Packet<B, TestPacketTypes>({1, 2});
	ps << Packet<A, TestPacketTypes>({5, 4});
	ps << Packet<AA, TestPacketTypes>({42, 41, 40});

	auto ibegin = ps.begin();
	auto iend = ps.end();

	EXPECT_EQ((*ibegin).TypeIndex(), TestPacketTypes::IndexOf<B>());
	const B& b = (*ibegin).As<B>();
	EXPECT_EQ(b.a, 1);
	EXPECT_EQ(b.b, 2);
	++ibegin;
	EXPECT_EQ((*ibegin).TypeIndex(), TestPacketTypes::IndexOf<A>());
	const A& a = (*ibegin).As<A>();
	EXPECT_EQ(a.i, 5);
	EXPECT_EQ(a.b, 4);
	++ibegin;
	EXPECT_EQ((*ibegin).TypeIndex(), TestPacketTypes::IndexOf<AA>());
	const AA& aa = (*ibegin).As<AA>();
	EXPECT_EQ(aa.i, 42);
	EXPECT_EQ(aa.b, 41);
	EXPECT_EQ(aa.c, 40);
	++ibegin;
	EXPECT_EQ(ibegin, iend);
}

TEST(Collections, PacketStream_Invoke)
{
	using namespace Cpf;

	using StreamType = PacketStream<TestPacketTypes>;
	StreamType ps;

	ps << Packet<B, TestPacketTypes>({ 1, 2 });
	ps << Packet<A, TestPacketTypes>({ 5, 4 });
	ps << Packet<AA, TestPacketTypes>({ 42, 41, 40 });

	for (auto it : testResult)
		EXPECT_FALSE(it);
	int i = 0;
	for (auto it : ps)
	{
		StreamType::TypeList::Call(it.TypeIndex(), it.Payload(), i, ++i);
	}
	for (auto it : testResult)
		EXPECT_TRUE(it);
}
#endif
