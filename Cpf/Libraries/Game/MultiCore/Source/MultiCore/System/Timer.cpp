//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System/iTimer.hpp"
#include "Timer.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

/**
 Default constructor.
 */
Timer::Timer()
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
COM::Result CPF_STDCALL Timer::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;

		case iTimer::kIID.GetID():
			*outIface = static_cast<iTimer*>(this);
			break;

		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

/**
 Initializes this object.
 @param [in,out] owner The pipeline that owns this object.
 @param name The name of the timer.
 @return Success/failure code.
 */
COM::Result CPF_STDCALL Timer::Initialize(Plugin::iRegistry* rgy, const char* name)
{
	mID = SystemID(name, strlen(name));

	mStart = Time::Now();
	mTime = mStart;

	rgy->Create(nullptr, kSingleUpdateStageCID, iSingleUpdateStage::kIID, mpUpdate.AsVoidPP());
	mpUpdate->Initialize(this, iStage::kExecute.GetString());
	mpUpdate->SetUpdate(&Timer::_Update, this);
	AddStage(mpUpdate);
	return COM::kOK;
}

COM::Result CPF_STDCALL Timer::FindStage(StageID id, iStage** outStage) const
{
	for (const auto& stage : mStages)
	{
		if (stage->GetID() == id)
		{
			stage->AddRef();
			*outStage = stage;
			return COM::kOK;
		}
	}
	return COM::kInvalid;
}

SystemID CPF_STDCALL Timer::GetID() const
{
	return mID;
}

COM::Result CPF_STDCALL Timer::GetStages(int32_t* count, iStage** outStages) const
{
	if (count)
	{
		if (outStages)
		{
			if (int32_t(mStages.size()) > *count)
				return COM::kNotEnoughSpace;
			int32_t index = 0;
			for (auto stage : mStages)
				outStages[index++] = stage;
			return COM::kOK;
		}
		else
		{
			*count = int32_t(mStages.size());
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Timer::GetInstructions(int32_t* count, Instruction* instructions)
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
				return COM::kOK;
			}
			return COM::kNotEnoughSpace;
		}
		*count = int32_t(result.size());
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

void CPF_STDCALL Timer::AddDependency(BlockDependency dep)
{
	mDependencies.push_back(dep);
}

COM::Result CPF_STDCALL Timer::GetDependencies(iPipeline* owner, int32_t* count, BlockDependency* deps)
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
			return COM::kOK;
		}
		else
		{
			*count = int32_t(result.size());
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

COM::Result CPF_STDCALL Timer::Configure(iPipeline*)
{
	return COM::kOK;
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

void Timer::_Update(Concurrency::ThreadContext&, void* context)
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
COM::Result Timer::AddStage(iStage* stage)
{
	if (stage && stage->IsEnabled())
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

COM::Result Timer::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return COM::kOK;
		}
	}
	return COM::kInvalidParameter;
}

