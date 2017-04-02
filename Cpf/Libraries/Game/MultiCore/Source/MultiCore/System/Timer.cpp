//////////////////////////////////////////////////////////////////////////
#include "MultiCore/System/iTimer.hpp"
#include "Timer.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace MultiCore;

//////////////////////////////////////////////////////////////////////////
Timer::Timer()
	: mPaused(false)
	, mpUpdate(nullptr)
{
}

Timer::~Timer()
{
	RemoveStage(mpUpdate->GetID());
}

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

COM::Result CPF_STDCALL Timer::Initialize(iPipeline* owner, const char* name)
{
	mpOwner = owner;
	mID = SystemID(name, strlen(name));

	mStart = Time::Now();
	mTime = mStart;

	mpUpdate.Adopt(reinterpret_cast<SingleUpdateStage*>(Stage::Create(SingleUpdateStage::kID, nullptr, this, Stage::kExecute.GetString())));
	mpUpdate->SetUpdate(&Timer::_Update, this);
	AddStage(mpUpdate);
	return COM::kOK;
}

iPipeline* CPF_STDCALL Timer::GetOwner() const
{
	return mpOwner;
}

COM::Result CPF_STDCALL Timer::GetStage(StageID id, Stage** outStage) const
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

int32_t CPF_STDCALL Timer::GetStageCount() const
{
	return int32_t(mStages.size());
}

Stage* CPF_STDCALL Timer::GetStage(int32_t index)
{
	return mStages[index];
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
				stage->GetInstructions(GetID(), &instructionCount, nullptr);
				Vector<Instruction> insts(instructionCount);
				stage->GetInstructions(GetID(), &instructionCount, insts.data());
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

COM::Result CPF_STDCALL Timer::GetDependencies(int32_t* count, BlockDependency* deps)
{
	if (count)
	{
		BlockDependencies result;
		for (const auto& dep : mDependencies)
		{
			Stage* depStage = nullptr;
			GetOwner()->GetStage(dep.mDependent.mSystem, dep.mDependent.mStage, &depStage);
			Stage* targetStage = nullptr;
			GetOwner()->GetStage(dep.mTarget.mSystem, dep.mTarget.mStage, &targetStage);
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

COM::Result CPF_STDCALL Timer::Configure()
{
	return COM::kOK;
}

//////////////////////////////////////////////////////////////////////////
Time::Value Timer::GetTime() const
{
	return mTime - mStart;
}

float Timer::GetDeltaTime() const
{
	return float(Time::Seconds(mDelta));
}

bool Timer::IsPaused() const
{
	return mPaused;
}

void Timer::SetPause(bool flag)
{
	if (!flag && flag)
	{
		mStart = Time::Now();
		mTime = mStart + mDelta;
	}
	mPaused = flag;
}

void Timer::Pause()
{
	mPaused = true;
}

void Timer::Resume()
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
bool Timer::AddStage(Stage* stage)
{
	if (stage && stage->IsEnabled())
	{
		stage->AddRef();
		mStages.emplace_back(stage);
		return true;
	}
	return false;
}

bool Timer::RemoveStage(StageID id)
{
	for (int i = 0; i < mStages.size(); ++i)
	{
		if (mStages[i]->GetID() == id)
		{
			mStages.erase(mStages.begin() + i);
			return true;
		}
	}
	return false;
}

