//////////////////////////////////////////////////////////////////////////
#pragma once
#include "iRenderSystem.hpp"

namespace Cpf
{
	class RenderSystem : public tRefCounted<iRenderSystem>
	{
	public:
		RenderSystem(COM::iUnknown*);

		// iUnknown.
		COM::Result QueryInterface(COM::InterfaceID id, void** outIface) override;

		// iStageList.
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL AddStage(MultiCore::iStage* stage) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID id) override;

		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		// iSystem.
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override;

	private:
		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;
	};
}
