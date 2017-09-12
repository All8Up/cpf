//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/../../Source/MultiCore/PlanBuilder.hpp"
#include <gtest/gtest.h>

TEST(MultiCore, DependencySolver_Basic)
{
#if 0
	using namespace CPF;
	using namespace MultiCore;

	DependencySolver solver;
	solver.AddStage(SystemID(0), StageID(1));
	solver.AddStage(SystemID(0), StageID(2));
	solver.AddStage(SystemID(0), StageID(3));
	solver.AddStage(SystemID(1), StageID(1));
	solver.AddStage(SystemID(1), StageID(2));
	solver.AddStage(SystemID(1), StageID(3));
	solver.AddStage(SystemID(1), StageID(4));
	solver.AddStage(SystemID(2), StageID(1));
	solver.AddStage(SystemID(2), StageID(2));
	solver.AddStage(SystemID(3), StageID(1));
	solver.AddStage(SystemID(3), StageID(2));
	solver.AddStage(SystemID(3), StageID(3));
	solver.AddStage(SystemID(3), StageID(4));
	solver.AddStage(SystemID(3), StageID(5));

	solver.AddDependencies({
		// Setup a series of dependencies for stages in system 0.
		{
			{ SystemID(0), StageID(3) },
			{ SystemID(0), StageID(2) }
		},
		{
			{ SystemID(0), StageID(2) },
			{ SystemID(0), StageID(1) }
		},
		// Setup a series of dependencies for stages in system 1.
		{
			{ SystemID(1), StageID(4) },
			{ SystemID(1), StageID(3) }
		},
		{
			{ SystemID(1), StageID(3) },
			{ SystemID(1), StageID(2) }
		},
		{
			{ SystemID(1), StageID(2) },
			{ SystemID(1), StageID(1) }
		},
		// Setup a series of dependencies for stages in system 2.
		{
			{ SystemID(2), StageID(2) },
			{ SystemID(2), StageID(1) }
		},
		// Setup a series of dependencies for stages in system 3.
		{
			{ SystemID(3), StageID(5) },
			{ SystemID(3), StageID(4) }
		},
		{
			{ SystemID(3), StageID(4) },
			{ SystemID(3), StageID(3) }
		},
		{
			{ SystemID(3), StageID(3) },
			{ SystemID(3), StageID(2) }
		},
		{
			{ SystemID(3), StageID(2) },
			{ SystemID(3), StageID(1) }
		},
		// Now make system 2 stage 1 depend on system 1 stage 2.
		{
			{ SystemID(2), StageID(1) },
			{ SystemID(1), StageID(2) }
		},
	});

	// NOTE: Using mark 1 eyeball to validate the chain right now.
	// This just validates that it believes it got it correct.
	EXPECT_TRUE(solver.Solve());
#endif
}
