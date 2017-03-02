//////////////////////////////////////////////////////////////////////////
#include "MultiCore/Types.hpp"

using namespace Cpf;
using namespace MultiCore;

bool SSBID::operator <(const SSBID& rhs) const
{
	if (mSystem < rhs.mSystem)
		return true;
	if (mSystem == rhs.mSystem)
	{
		if (mStage < rhs.mStage)
			return true;
		if (mStage == rhs.mStage)
		{
			if (mBlock < rhs.mBlock)
				return true;
		}
	}
	return false;
}


bool SSBID::operator ==(const SSBID& rhs) const
{
	return mSystem == rhs.mSystem && mStage == rhs.mStage && mBlock == rhs.mBlock;
}

//////////////////////////////////////////////////////////////////////////
BlockDependency::BlockDependency(SSBID dependent, SSBID target, DependencyPolicy policy)
	: mDependent(dependent)
	, mTarget(target)
	, mPolicy(policy)
{}
