//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Types.hpp"
#include "Instance.hpp"
#include "MultiCore/iSystem.hpp"
#include "MultiCore/iStage.hpp"
#include "Hash/HashString.hpp"
#include "Plugin/iClassInstance.hpp"

namespace Cpf
{
	class ExperimentalD3D12;

	static constexpr GOM::ClassID kInstanceSystemCID = GOM::ClassID("InstanceSystem"_crc64);

	class InstanceSystem : public tRefCounted<MultiCore::iSystem>
	{
	public:
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("iInstanceSystem"_crc64);

		using StageID = EntityService::StageID;

		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Instance Manager"_hashString);

		static constexpr MultiCore::StageID kBegin = Hash::Create<MultiCore::StageID_tag>("Instance Begin"_hashString);
		static constexpr MultiCore::StageID kEnd = Hash::Create<MultiCore::StageID_tag>("Instance End"_hashString);

		struct Desc : iSystem::Desc
		{
			MultiCore::SystemID mRenderSystemID;
			ExperimentalD3D12* mpApplication;
		};

		InstanceSystem(GOM::iUnknown*);

		Instance* GetInstances() const { return mpInstances; }

		// iBase
		GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

		// iSystem
		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, const char* name, const iSystem::Desc* desc) override;
		MultiCore::SystemID CPF_STDCALL GetID() const override;
		GOM::Result CPF_STDCALL Configure(MultiCore::iExecutionPlan*) override { return GOM::kOK; }

		// iStageList
		GOM::Result CPF_STDCALL FindStage(MultiCore::StageID id, MultiCore::iStage** outStage) const override;
		GOM::Result CPF_STDCALL GetStages(int32_t* count, MultiCore::iStage** outStages) const override;
		GOM::Result CPF_STDCALL GetInstructions(int32_t*, MultiCore::Instruction*) override;
		void CPF_STDCALL AddDependency(MultiCore::BlockDependency dep) override;
		GOM::Result CPF_STDCALL GetDependencies(MultiCore::iExecutionPlan* owner, int32_t*, MultiCore::BlockDependency*) override;

		GOM::Result CPF_STDCALL AddStage(MultiCore::iStage*) override;
		GOM::Result CPF_STDCALL RemoveStage(MultiCore::StageID) override;

		static GOM::Result Install(Plugin::iRegistry* regy)
		{
			return regy->Install(kInstanceSystemCID.GetID(), new Plugin::tClassInstance<InstanceSystem>());
		}
		static GOM::Result Remove(Plugin::iRegistry* regy)
		{
			return regy->Remove(kInstanceSystemCID.GetID());
		}

	private:
		static void _Begin(const Concurrency::WorkContext*, void* context);
		static void _End(const Concurrency::WorkContext*, void* context);

		MultiCore::SystemID mID;
		IntrusivePtr<MultiCore::iStageList> mpStages;

		ExperimentalD3D12* mpApp;
		MultiCore::SystemID mRenderID;
		Instance* mpInstances;
	};
}
