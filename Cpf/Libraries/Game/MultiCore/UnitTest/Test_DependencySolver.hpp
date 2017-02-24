//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/DependencySolver.hpp"
#include <gtest/gtest.h>

TEST(MultiCore, DependencySolver_Basic)
{
	using namespace Cpf;
	using namespace MultiCore;

	DependencySolver solver;
	solver.AddStage({ SystemID(0), StageID(1) });
	solver.AddStage({ SystemID(0), StageID(2) });
	solver.AddStage({ SystemID(0), StageID(3) });
	solver.AddStage({ SystemID(1), StageID(1) });
	solver.AddStage({ SystemID(1), StageID(2) });
	solver.AddStage({ SystemID(1), StageID(3) });
	solver.AddStage({ SystemID(1), StageID(4) });
	solver.AddStage({ SystemID(2), StageID(1) });
	solver.AddStage({ SystemID(2), StageID(2) });
	solver.AddStage({ SystemID(3), StageID(1) });
	solver.AddStage({ SystemID(3), StageID(2) });
	solver.AddStage({ SystemID(3), StageID(3) });
	solver.AddStage({ SystemID(3), StageID(4) });
	solver.AddStage({ SystemID(3), StageID(5) });

	solver.AddDependencies({ {ConcurrencyStyle::eConcurrent, {SystemID(2), StageID(1)}, {SystemID(0), StageID(1)}} });

	EXPECT_TRUE(solver.Solve());
}
