//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "Plugin/iClassInstance.hpp"

namespace CPF
{
	namespace MultiCore
	{
		class Timer : public tRefCounted<iTimer>
		{
		public:
			// Construction/Destruction.
			Timer(Plugin::iRegistry*, iUnknown*);
			virtual ~Timer();

			// iBase overrides.
			GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

			// System overrides.
			GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) override;
			GOM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			SystemID CPF_STDCALL GetID() const override;
			GOM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			GOM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			GOM::Result CPF_STDCALL GetDependencies(iExecutionPlan* owner, int32_t*, BlockDependency*) override;
			GOM::Result CPF_STDCALL Configure(iExecutionPlan*) override;

			// Timer interface.
			Time::Value CPF_STDCALL GetTime() override;
			float CPF_STDCALL GetDeltaTime() override;
			bool CPF_STDCALL IsPaused() override;
			void CPF_STDCALL SetPause(bool flag) override;
			void CPF_STDCALL Pause() override;
			void CPF_STDCALL Resume() override;

			GOM::Result CPF_STDCALL AddStage(iStage*);
			GOM::Result CPF_STDCALL RemoveStage(StageID);

		private:

			// Internal update function.
			static void _Update(const Concurrency::WorkContext*, void*);

			// Implementation data.
			Time::Value mTime;
			Time::Value mStart;
			Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<iSingleUpdateStage> mpUpdate;

			iExecutionPlan* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};
	}
}
