//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "Math/LargeVector.hpp"

using namespace CPF;
using namespace Math;

TEST(LargeVector, Construction_Extraction)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	using Sector = Type::SectorType;

	Type uninitialized; (void)uninitialized;  // Just tests that it compiles.

	// Simple test of origin.
	Type sector0Origin({ 0.0f, 0.0f, 0.0f }, Sector(0));
	EXPECT_NEAR(0.0f, ExtractVector3(sector0Origin).x, 0.01f);
	EXPECT_NEAR(0.0f, ExtractVector3(sector0Origin).y, 0.01f);
	EXPECT_NEAR(0.0f, ExtractVector3(sector0Origin).z, 0.01f);
	EXPECT_EQ(Sector(0), ExtractSector(sector0Origin));

	// Simple test of sector passing through.
	Type sector1Origin({ 0.0f, 0.0f, 0.0f }, Sector(1));
	EXPECT_NEAR(0.0f, ExtractVector3(sector1Origin).x, 0.01f);
	EXPECT_NEAR(0.0f, ExtractVector3(sector1Origin).y, 0.01f);
	EXPECT_NEAR(0.0f, ExtractVector3(sector1Origin).z, 0.01f);
	EXPECT_EQ(Sector(1), ExtractSector(sector1Origin));
}

TEST(LargeVector, Insertion)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	using Sector = Type::SectorType;

	Type test0({ 0.0f, 0.0f, 0.0f }, Sector(0));
	InsertVector(test0, {1.0f, 2.0f, 3.0f});
	EXPECT_NEAR(1.0f, ExtractVector3(test0).x, 0.01f);
	EXPECT_NEAR(2.0f, ExtractVector3(test0).y, 0.01f);
	EXPECT_NEAR(3.0f, ExtractVector3(test0).z, 0.01f);
	EXPECT_EQ(Sector(0), ExtractSector(test0));

	InsertSector(test0, Sector(5));
	EXPECT_NEAR(1.0f, ExtractVector3(test0).x, 0.01f);
	EXPECT_NEAR(2.0f, ExtractVector3(test0).y, 0.01f);
	EXPECT_NEAR(3.0f, ExtractVector3(test0).z, 0.01f);
	EXPECT_EQ(Sector(5), ExtractSector(test0));
}

TEST(LargeVector, Normalize)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	using Sector = Type::SectorType;

	Type test0({ 5.0f, 5.0f, 5.0f }, Sector(0));
	test0 = Normalize(test0);

	// Should be unchanged since this is 'inclusive'.
	EXPECT_NEAR(5.0f, ExtractVector3(test0).x, 0.01f);
	EXPECT_NEAR(5.0f, ExtractVector3(test0).y, 0.01f);
	EXPECT_NEAR(5.0f, ExtractVector3(test0).z, 0.01f);
	EXPECT_EQ(Sector(0), ExtractSector(test0));

	InsertVector(test0, {5.1f, 5.1f, 5.1f});
	test0 = Normalize(test0);

	// Now it should have moved to the 1, 1, 1 sector.
	EXPECT_NEAR(-4.9f, ExtractVector3(test0).x, 0.01f);
	EXPECT_NEAR(-4.9f, ExtractVector3(test0).y, 0.01f);
	EXPECT_NEAR(-4.9f, ExtractVector3(test0).z, 0.01f);
	EXPECT_EQ(Sector(1, 1, 1), ExtractSector(test0));

	//////////////////////////////////////////////////////////////////////////
	Type test1({ -5.0f, -5.0f, -5.0f }, Sector(0));
	test1 = Normalize(test1);

	// Should be moved to the next sector since negative quadrants are 'exclusive'.
	EXPECT_NEAR(5.0f, ExtractVector3(test1).x, 0.01f);
	EXPECT_NEAR(5.0f, ExtractVector3(test1).y, 0.01f);
	EXPECT_NEAR(5.0f, ExtractVector3(test1).z, 0.01f);
	EXPECT_EQ(Sector(-1, -1, -1), ExtractSector(test1));
}

TEST(LargeVector, Relative)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	using Sector = Type::SectorType;

	{
		Type test0({ 0.0f, 0.0f, 0.0f }, Sector(0));
		Type test1({ 0.0f, 0.0f, 0.0f }, Sector(5, 5, 5));

		auto delta = GetRelative(test0, test1);
		EXPECT_NEAR(50.0f, delta.x, 0.01f);
		EXPECT_NEAR(50.0f, delta.y, 0.01f);
		EXPECT_NEAR(50.0f, delta.z, 0.01f);
	}

	{
		Type test0({ 1.0f, 1.0f, 1.0f }, Sector(0));
		Type test1({ -1.0f, -1.0f, -1.0f }, Sector(5, 5, 5));

		auto delta = GetRelative(test0, test1);
		EXPECT_NEAR(48.0f, delta.x, 0.01f);
		EXPECT_NEAR(48.0f, delta.y, 0.01f);
		EXPECT_NEAR(48.0f, delta.z, 0.01f);
	}
}
