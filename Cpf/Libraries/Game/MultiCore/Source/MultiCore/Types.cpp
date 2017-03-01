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
StageBlockID::StageBlockID(StageID stageID, BlockID blockID)
	: mStage(stageID)
	, mBlock(blockID)
{}

StageBlockID::StageBlockID(const SSBID& ssbid)
	: mStage(ssbid.mStage)
	, mBlock(ssbid.mBlock)
{}

//////////////////////////////////////////////////////////////////////////
BlockDependency::BlockDependency(SSBID dependent, SSBID target, BlockPolicy policy)
	: mDependent(dependent)
	, mTarget(target)
	, mPolicy(policy)
{}
