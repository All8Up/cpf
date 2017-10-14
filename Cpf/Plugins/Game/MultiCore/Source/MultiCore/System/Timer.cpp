//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System/iTimer.hpp"
#include "Timer.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "CPF/Logging.hpp"

using namespace CPF;
using namespace MultiCore;

/**
 Default constructor.
 */
Timer::Timer(Plugin::iRegistry*, iUnknown*)
	: mPaused(false)
	, mpUpdate(nullptr)
{
}

/**
 Destructor.
 */
Timer::~Timer()
{
	RemoveStage(mpUpdate->GetID());
}

/**
 Queries for a desired interface.
 @param id The interface id.
 @param [in,out] outIface The output interface pointer.
 @return Success/failure code.
 */
GOM::Result CPF_STDCALL Timer::QueryInterface(uint64_t id, void** outIface)
{
	if (outIface)
	{
		switch (id)
		{
		case GOM::iUnknown::kIID.GetID():
			*outIface = static_cast<GOM::iUnknown*>(this);
			break;

		case iTimer::kIID.GetID():
			*outIface = static_cast<iTimer*>(this);
			break;

		default:
			return GOM::kUnknownInterface;
		}
		AddRef();
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

/**
 Initializes this object.
 @param [in,out] owner The pipeline that owns this object.
 @param name The name of the timer.
 @return Success/failure code.
 */
GOM::Result CPF_STDCALL Timer::Initialize(Plugin::iRegistry* rgy, const char* name, const Desc*)
{
	mID = SystemID(name, strlen(name));

	mStart = Time::Now();
	mTime = mStart;

	rgy->Create(nullptr, kSingleUpdateStageCID.GetID(), iSingleUpdateStage::kIID.GetID(), mpUpdate.AsVoidPP());
	mpUpdate->Initialize(this, iStage::kExecute.GetString());
	mpUpdate->SetUpdate(&Timer::_Update, this);
	AddStage(mpUpdate);
	return GOM::kOK;
}

GOM::Result CPF_STDCALL Timer::FindStage(StageID id, iStage** outStage) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			*outStage = stage;
			return GOM::kOK;
		}
	}
	return GOM::kInvalid;
}

SystemID CPF_STDCALL Timer::GetID() const
{
	return mID;
}

GOM::Result CPF_STDCALL Timer::GetStages(int32_t* count, iStage** outStages) const
{
	if (count)
	{
		if (outStages)
		{
			if (int32_t(mStages.size()) > *count)
				return GOM::kNotEnoughSpace;
			int32_t index = 0;
			for (auto stage : mStages)
				outStages[index++] = stage;
			return GOM::kOK;
		}
		else
		{
			*count = int32_t(mStages.size());
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Timer::GetInstructions(int32_t* count, Instruction* instructions)
{
	if (count)
	{
		Instructions result;
		for (const auto& stage : mStages)
		{
			if (stage->IsEnabled())
			{
				int32_t instructionCount = 0;
				stage->GetInstructions(&instructionCount, nullptr);
				Vector<Instruction> insts(instructionCount);
				stage->GetInstructions(&instructionCount, insts.data());
				result.insert(result.end(), insts.begin(), insts.end());
			}
		}
		if (instructions)
		{
			if (*count >= result.size())
			{
				int32_t index = 0;
				for (auto& inst : result)
					instructions[index++] = inst;
				return GOM::kOK;
			}
			return GOM::kNotEnoughSpace;
		}
		*count = int32_t(result.size());
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

void CPF_STDCALL Timer::AddDependency(BlockDependency dep)
{
	mDependencies.push_back(dep);
}

GOM::Result CPF_STDCALL Timer::GetDependencies(iExecutionPlan* owner, int32_t* count, BlockDependency* deps)
{
	if (count)
	{
		BlockDependencies result;
		for (const auto& dep : mDependencies)
		{
			iStage* depStage = nullptr;
			owner->GetStage(dep.mDependent.mSystem, dep.mDependent.mStage, &depStage);
			iStage* targetStage = nullptr;
			owner->GetStage(dep.mTarget.mSystem, dep.mTarget.mStage, &targetStage);
			if (depStage && depStage->IsEnabled() &&
				targetStage && targetStage->IsEnabled())
			{
				result.push_back(dep);
			}
			else
			{
				CPF_LOG(MultiCore, Info) << "Dropped disabled dependency.";
			}
		}

		if (deps)
		{
			int32_t index = 0;
			for (const auto& dep : result)
				deps[index++] = dep;
			return GOM::kOK;
		}
		else
		{
			*count = int32_t(result.size());
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

GOM::Result CPF_STDCALL Timer::Configure(iExecutionPlan*)
{
	return GOM::kOK;
}

//////////////////////////////////////////////////////////////////////////
Time::Value CPF_STDCALL Timer::GetTime()
{
	return mTime - mStart;
}

float CPF_STDCALL Timer::GetDeltaTime()
{
	return float(Time::Seconds(mDelta));
}

bool CPF_STDCALL Timer::IsPaused()
{
	return mPaused;
}

void CPF_STDCALL Timer::SetPause(bool flag)
{
	if (!flag && flag)
	{
		mStart = Time::Now();
		mTime = mStart + mDelta;
	}
	mPaused = flag;
}

void CPF_STDCALL Timer::Pause()
{
	mPaused = true;
}

void CPF_STDCALL Timer::Resume()
{
	SetPause(false);
}

void Timer::_Update(const Concurrency::WorkContext*, void* context)
{
	Timer* self = reinterpret_cast<Timer*>(context);
	if (!self->mPaused)
	{
		Time::Value now = Time::Now();
		self->mDelta = now - self->mTime;
		self->mTime = now;
	}
}


//////////////////////////////////////////////////////////////////////////
GOM::Result Timer::AddStage(iStage* stage)
{
	if (stage && stage->IsEnabled())
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return GOM::kOK;
	}
	return GOM::kInvalidParameter;
}

GOM::Result Timer::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return GOM::kOK;
		}
	}
	return GOM::kInvalidParameter;
}

