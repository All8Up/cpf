//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "Instance.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Hash/HashString.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	class InstanceSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		using StageID = EntityService::StageID;

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Instance Manager"_hashString);

		static constexpr MultiCore::StageID kBegin = Hash::Create<MultiCore::StageID_tag>("Instance Begin"_hashString);
		static constexpr MultiCore::StageID kEnd = Hash::Create<MultiCore::StageID_tag>("Instance End"_hashString);

		struct Desc : iSystem::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(Plugin::iRegistry*, const char* name, const Desc* desc);

		Instance* GetInstances() const { return mpInstances; }

		// iUnknown
		COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

		// iSystem
		COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		COM::Result CPF_STDCALL Configure(MultiCore::iPipeline*) override { return COM::kOK; }

		// iStageList
		COM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		COM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		COM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		COM::Result CPF_STDCALL GetDependencies(MultiCore::iPipeline* owner, int32_t*, MultiCore::BlockDependency*) override;

		COM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		COM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

		static bool Install()
		{
			return iSystem::Install(kID, &InstanceSystem::_Creator);
		}
		static bool Remove()
		{
			return iSystem::Remove(kID);
		}

	private:
		static iSystem* _Creator(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc)
		{
			return new InstanceSystem(rgy, name, static_cast<const Desc*>(desc));
		}

		static void _Begin(Concurrency::ThreadContext&, void* context);
		static void _End(Concurrency::ThreadContext&, void* context);

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}
