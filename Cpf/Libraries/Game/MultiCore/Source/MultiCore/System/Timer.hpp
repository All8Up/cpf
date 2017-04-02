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
		class CPF_EXPORT_MULTICORE Timer : public tRefCounted<iTimer>
		{
		public:
			// Construction/Destruction.
			Timer();
			~Timer() override;

			// iUnknown overrides.
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

			// System overrides.
			COM::Result CPF_STDCALL Initialize(iPipeline* owner, const char* name) override;
			iPipeline* CPF_STDCALL GetOwner() const override;
			COM::Result CPF_STDCALL GetStage(StageID id, Stage** outStage) const override;
			SystemID CPF_STDCALL GetID() const override;
			int32_t CPF_STDCALL GetStageCount() const override;
			Stage* CPF_STDCALL GetStage(int32_t index) override;
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;
			COM::Result CPF_STDCALL Configure();

			// Timer interface.
			Time::Value CPF_STDCALL GetTime() const override;
			float CPF_STDCALL GetDeltaTime() const override;
			bool CPF_STDCALL IsPaused() const override;
			void CPF_STDCALL SetPause(bool flag) override;
			void CPF_STDCALL Pause() override;
			void CPF_STDCALL Resume() override;

		private:
			bool AddStage(Stage*);
			bool RemoveStage(StageID);

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Time::Value mTime;
			Time::Value mStart;
			Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<SingleUpdateStage> mpUpdate;

			iPipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};

		class TimerClass : public tRefCounted<Plugin::iClassInstance>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID, void**) override { return COM::kNotImplemented; }
			COM::Result CPF_STDCALL CreateInstance(Plugin::iRegistry*, COM::iUnknown*, COM::iUnknown** outIface) override
			{
				if (outIface)
				{
					*outIface = new Timer();
					return *outIface ? COM::kOK : COM::kOutOfMemory;
				}
				return COM::kInvalidParameter;
			}
		};
	}
}
