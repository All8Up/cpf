//////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "Math/LargeVector.hpp"

using namespace CPF;
using namespace Math;

/*
Use outline.
All large vectors can be described by the following equation:
p' = (sectorxyz * scale) + relative.xyz;
This is the 'normalized' form of a large vector such that the following rules
hold true: relative.x/y/z are all in the range of 5>= relative <-5.  (Note: the
rules are 'inclusive' on the positive side and 'exclusive' on the negative side.)
Given these rules and equations, taking the large vector to different spaces is
fairly simple.  Zero out the sector by pre-adding into the relative portion, likely
requiring it to be double storage, and you are now in world space.  Simply dropping
the sector*scale gives a vector in sector relative space.  Other variations are
possible.

Some example use cases:
LargeVector3fv p0, p1;
Vector3fv v0;

// No coordinate space conversion.
double distance = Magnitude (p1 - p2);
p1 = p0 + (v0 * deltaTime);
p0.x = 0;  // Compile error.  Access to elements only allowed through world or relative views.

// Working in relative space.
p0.relative.x = 0;
auto x = p0.relative.x; // = 0 (sector remains unchanged)
p0.relative.x = 1000.0;
auto xx = p0.relative.x; // = 0 (sector absorbed the overflow)

// Note: potential confusion issue here.  If someone wishes to project everything onto a zero plane
// such as p0.relative.z = 0, that is *wrong*, they must use p0.world.z = 0, not relative.  This
// could potentially be the cause of some bugs...

// Working in world space.
p0.world.x = 0; // Sets x and sector x to zero.
*/

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

TEST(LargeVector, ValidateSize)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	EXPECT_TRUE(sizeof(Type) == sizeof(typename Type::Description::StorageType));
}

TEST(LargeVector, WorldRepresentation)
{
	using Type = LargeVector<LargeVectorDesc_FI>;
	Type position;
	auto test = position.world;
}
