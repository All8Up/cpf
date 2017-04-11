//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Export.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/System/iTimer.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	namespace MultiCore
	{
		class Timer : public tRefCounted<iTimer>
		{
		public:
			// Construction/Destruction.
			Timer();
			virtual ~Timer();

			// iUnknown overrides.
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

			// System overrides.
			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) override;
			COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			SystemID CPF_STDCALL GetID() const override;
			COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(iPipeline* owner, int32_t*, BlockDependency*) override;
			COM::Result CPF_STDCALL Configure(iPipeline*) override;

			// Timer interface.
			Time::Value CPF_STDCALL GetTime() override;
			float CPF_STDCALL GetDeltaTime() override;
			bool CPF_STDCALL IsPaused() override;
			void CPF_STDCALL SetPause(bool flag) override;
			void CPF_STDCALL Pause() override;
			void CPF_STDCALL Resume() override;

			COM::Result CPF_STDCALL AddStage(iStage*);
			COM::Result CPF_STDCALL RemoveStage(StageID);

		private:

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Time::Value mTime;
			Time::Value mStart;
			Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<iSingleUpdateStage> mpUpdate;

			iPipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};
	}
}
